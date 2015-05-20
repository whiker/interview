#include "ini_parser.h"

#include <iostream>
using namespace std;

namespace qh
{
    std::string INIParser::NULL_STR_("");

    bool INIParser::Parse(const std::string& ini_file_path)
    {
        return false;
    }

    bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator)
    {
        if (ini_data == NULL || ini_data_len == 0)
            return true;

        const char* ini_end = ini_data + ini_data_len;
        const char* LineSepe = line_seperator.data();
        const char* KvSepe = key_value_seperator.data();
        const char* currEnd=NULL;  // current key_value line
        const char* currSepe=NULL;

        const size_t LineSepeLen = line_seperator.length();
        const size_t KvSepeLen = key_value_seperator.length();

        key_value_.clear();

        while (ini_data != ini_end)
        {
            currEnd = myStrstr(ini_data, ini_end - ini_data, LineSepe);
            if (currEnd == ini_data)
            {
                ini_data += LineSepeLen;
                continue;
            }
            else if (currEnd == NULL)
                currEnd = ini_end;

            currSepe = myStrstr(ini_data, currEnd - ini_data, KvSepe);
            if (currSepe == NULL || currSepe == ini_data)
                return false;

            std::string key(ini_data, currSepe - ini_data);
            currSepe += KvSepeLen;
            std::string value(currSepe, currEnd - currSepe);
            key_value_[key] = value;

            if (currEnd == ini_end)
                break;
            ini_data = currEnd + LineSepeLen;
        }

        return true;
    }

    const std::string& INIParser::Get(const std::string& key, bool* found)
    {
        KeyValuePairsIter iter = key_value_.find(key);
        bool ret = iter != key_value_.end();

        if (found)
            *found = ret;

        if (ret)
            return iter->second;
        else
            return NULL_STR_;
    }

    const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
    {
        return NULL_STR_;
    }

    const char* INIParser::myStrstr(const char* src, const size_t len, const char* dst)
    {
        if (src == NULL) return NULL;
        if (dst == NULL) return src;

        size_t i, j, leave;
        for (i = 0; i < len; i++)
        {
            leave = len - i;
            for (j = 0; j < leave && src[j]==dst[j]; j++)
            {
                if (!dst[j+1])
                    return src;
            }
            src++;
        }
        return NULL;
    }
}