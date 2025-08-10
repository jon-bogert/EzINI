#pragma once

// NOTE: This only supports the basic "key=value" aspect of the INI format with no other advanced features

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace xe
{
	class EzIni
	{
	public:
		bool OpenFile(const std::filesystem::path& filePath)
		{
			std::ifstream file(filePath);
			if (!file.is_open())
				return false;

			Parse(file);

			return true;
		}

		void Parse(const std::string& string)
		{
			std::stringstream stream(string);
			Parse(stream);
		}

		void Parse(std::istream& stream)
		{
			Clear();
			std::string line;

			while (std::getline(stream, line))
			{
				while (!line.empty() && (line.back() == ' ' || line.back() == '\t'))
					line.pop_back();

				if (line.empty())
					return;

				if (line.front() == '[' || line.front() == ';')
					return;

				std::stringstream lineStream(line);
				std::string key;
				std::string val;

				std::getline(lineStream, key, '=');
				std::getline(lineStream, val);

				m_values[key] = val;
				m_keyOrder.push_back(key);
			}
		}

		std::string GetString()
		{
			std::stringstream stream;
			stream << *this;
			return stream.str();
		}

		bool SaveFile(const std::filesystem::path& filePath)
		{
			std::ofstream file(filePath);
			if (!file.is_open())
				return false;

			file << *this;

			return true;
		}

		std::string& operator[](const std::string& key)
		{
			if (!Contains(key))
			{
				m_keyOrder.push_back(key);
			}
			return m_values[key];
		}

		const std::string& operator[](const std::string& key) const
		{
			return m_values.at(key);
		}

		size_t Size() const
		{
			return m_keyOrder.size();
		}

		bool Remove(const std::string& key)
		{
			auto valResult = m_values.find(key);
			if (valResult == m_values.end())
				return false;

			m_values.erase(valResult);
			auto keyResult = std::find_if(m_keyOrder.begin(), m_keyOrder.end(), [&](const std::string& v) { return v == key; });
			m_keyOrder.erase(keyResult);
			return true; 
		}

		void Clear()
		{
			m_keyOrder.clear();
			m_values.clear();
		}

		bool Contains(const std::string& key)
		{
			return m_values.find(key) != m_values.end();
		}

		const std::vector<std::string>& KeyOrder() const
		{
			return m_keyOrder;
		}

		friend std::ostream& operator<<(std::ostream& stream, const EzIni& self)
		{
			for (size_t i = 0; i < self.Size(); ++i)
			{
				const std::string& key = self.m_keyOrder[i];
				stream << key << '=' << self[key] << std::endl;
			}
			return stream;
		}

	private:
		std::vector<std::string> m_keyOrder;
		std::unordered_map<std::string, std::string> m_values;
	};
}