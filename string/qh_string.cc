#include "qh_string.h"

#include <string.h>

namespace qh
{
    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
        : data_(NULL), len_(0)
    {
        _init(s, s ? strlen(s) : 0);
    }

    string::string( const char* s, size_t len )
        : data_(NULL), len_(0)
    {
        _init(s, len);
    }

    string::string( const string& rhs )
        : data_(NULL), len_(0)
    {
        _init(rhs.data_, rhs.len_);
    }

    string& string::operator=( const string& rhs )
    {
        if (&rhs != this)
        {
            _release();
            _init(rhs.data_, rhs.len_);
        }
        return *this;
    }

    string::~string()
    {
        _release();
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        return data_;
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char* string::operator[]( size_t index )
    {
        if (index >= 0 && index < len_ && data_)
            return data_+index;
        else
            return NULL;
    }

    void string::_init( const char* s, size_t len )
    {
        if (s && len > 0)
        {
            int copylen = strlen(s);
            if (copylen > len)
                copylen = len;

            data_ = new char[copylen+1];
            if (data_)
            {
                memcpy(data_, s, copylen);
                data_[copylen] = '\0';
                len_ = copylen;
            }
            else
                len_ = 0;
        }
    }

    void string::_release()
    {
        if (data_)
        {
            delete[] data_;
            data_ = NULL;
        }
        len_ = 0;
    }
}
