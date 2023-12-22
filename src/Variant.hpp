#ifndef VARIANT_HPP_
#define VARIANT_HPP_

#include <cstring>
#include <sstream>
#include <string>

class Variant {
 public:
  using uchar = unsigned char;
  using ushort = unsigned short;
  using uint = unsigned int;
  using ulong = unsigned long;
  using ulonglong = unsigned long long;
  using wchar = wchar_t;

 public:
  enum Type {
    Invalid,
    Bool,
    Char,
    UChar,
    Short,
    UShort,
    Int,
    UInt,
    Long,
    ULong,
    LongLong,
    ULongLong,
    Float,
    Double,
    LongDouble,
    WChar,

    String,   // std::string
    WString,  // std::wstring
  };

  template <typename T>
  static Type typeID() {
    if (std::is_same_v<T, bool>) return Bool;
    if (std::is_same_v<T, char>) return Char;
    if (std::is_same_v<T, uchar>) return UChar;
    if (std::is_same_v<T, wchar_t>) return WChar;
    if (std::is_same_v<T, short>) return Short;
    if (std::is_same_v<T, ushort>) return UShort;
    if (std::is_same_v<T, int>) return Int;
    if (std::is_same_v<T, uint>) return UInt;
    if (std::is_same_v<T, long>) return Long;
    if (std::is_same_v<T, ulong>) return ULong;
    if (std::is_same_v<T, long long>) return LongLong;
    if (std::is_same_v<T, ulonglong>) return ULongLong;
    if (std::is_same_v<T, float>) return Float;
    if (std::is_same_v<T, double>) return Double;
    if (std::is_same_v<T, long double>) return LongDouble;
    if (std::is_same_v<T, std::string>) return String;
    if (std::is_same_v<T, std::wstring>) return WString;

    return Invalid;
  }

 public:
  Variant() : _d(Invalid) {}

  ~Variant() {
    if (String == _d.type) {
      if (_d.data.ptr) safe_delete_void_ptr<char *>(_d.data.ptr);
    } else if (WString == _d.type) {
      if (_d.data.ptr) safe_delete_void_ptr<wchar_t *>(_d.data.ptr);
    }
  }

  Variant(bool b) : _d(Bool) { _d.data.b = b; }

  Variant(char c) : _d(Char) { _d.data.c = c; }

  Variant(uchar uc) : _d(UChar) { _d.data.uc = uc; }

  Variant(wchar_t wc) : _d(WChar) { _d.data.wc = wc; }

  Variant(short s) : _d(Short) { _d.data.s = s; }
  Variant(ushort us) : _d(UShort) { _d.data.us = us; }
  Variant(int i) : _d(Int) { _d.data.i = i; }
  Variant(uint ui) : _d(UInt) { _d.data.ui = ui; }
  Variant(long l) : _d(Long) { _d.data.l = l; }
  Variant(ulong ul) : _d(ULong) { _d.data.ul = ul; }
  Variant(long long ll) : _d(LongLong) { _d.data.ll = ll; }
  Variant(ulonglong ull) : _d(ULongLong) { _d.data.ull = ull; }
  Variant(float f) : _d(Float) { _d.data.f = f; }
  Variant(double d) : _d(Double) { _d.data.d = d; }
  Variant(long double ld) : _d(LongDouble) { _d.data.ld = ld; }

  Variant(const char *str) : _d(String) {
    if (!str) {
      make_invalid();
    } else {
      size_t len = strlen(str);
      _d.data.ptr = new char[strlen(str) + 1];
#if defined(_MSC_VER)
      strcpy_s(static_cast<char *>(_d.data.ptr), strlen(str) + 1, str);
#elif defined(__GNUC__)
      strcpy(static_cast<char *>(_d.data.ptr), str);
#endif
    }
  }

  Variant(const wchar_t *wstr) {
    if (!wstr) {
      make_invalid();
    } else {
      _d.data.ptr = new char[wcslen(wstr) + 1];
#if defined(_MSC_VER)
      wcscpy_s((wchar_t *)_d.data.ptr, wcslen(wstr) + 1, wstr);
#elif defined(__GNUC__)
      wcscpy((wchar_t *)_d.data.ptr, wstr);
#endif
    }
  }

  Variant(const std::string &str) : _d(String) {
    if (str.empty()) {
      make_invalid();
    } else {
      _d.data.ptr = new char[str.size() + 1];
#if defined(_MSC_VER)
      strcpy_s((char *)_d.data.ptr, str.size() + 1, str.c_str());
#elif defined(__GNUC__)
      strcpy((char *)_d.data.ptr, str.c_str());
#endif
    }
  }

  Variant(const std::wstring &wstr) : _d(WString) {
    if (wstr.empty()) {
      make_invalid();
    } else {
      _d.data.ptr = new wchar_t[wstr.size() + 1];
#if defined(_MSC_VER)
      wcscpy_s((wchar_t *)_d.data.ptr, wstr.size() + 1, wstr.c_str());
#elif defined(__GNUC__)
      wcscpy((wchar_t *)_d.data.ptr, wstr.c_str());
#endif
    }
  }

  Variant(const Variant &other) : _d(other._d) {
    if (String == _d.type) {
      _d.data.ptr =
          new char[strlen(static_cast<char *>(other._d.data.ptr)) + 1];
#if defined(_MSC_VER)
      strcpy_s(static_cast<char *>(_d.data.ptr),
               strlen(static_cast<char *>(other._d.data.ptr)) + 1,
               static_cast<char *>(other._d.data.ptr));
#elif defined(__GNUC__)
      strcpy(static_cast<char *>(_d.data.ptr),
             static_cast<char *>(other._d.data.ptr));
#endif
    } else if (WString == _d.type) {
      _d.data.ptr =
          new char[wcslen(static_cast<wchar_t *>(other._d.data.ptr)) + 1];
#if defined(_MSC_VER)
      wcscpy_s(static_cast<wchar_t *>(_d.data.ptr),
               wcslen(static_cast<wchar_t *>(other._d.data.ptr)) + 1,
               static_cast<wchar_t *>(other._d.data.ptr));
#elif defined(__GNUC__)
      wcscpy(static_cast<wchar_t *>(_d.data.ptr),
             static_cast<wchar_t *>(other._d.data.ptr));
#endif
    }
  }
  Variant(Variant &&other) : _d(other._d) {
    if (String == other._d.type || WString == other._d.type) {
      this->_d.data.ptr = other._d.data.ptr;
      other.make_invalid();
    }
  }

  Variant &operator=(const Variant &other) {
    if (this == &other) return *this;
    if (String == _d.type || WString == _d.type) {
      if (_d.data.ptr) {
        delete[] (char *)_d.data.ptr;
        _d.data.ptr = nullptr;
      }
    }
    if (Invalid == other._d.type) {
      make_invalid();
      return *this;
    } else if (String == other._d.type) {
      _d.data.ptr =
          new char[strlen(static_cast<char *>(other._d.data.ptr)) + 1];
#if defined(_MSC_VER)
      strcpy_s(static_cast<char *>(_d.data.ptr),
               strlen(static_cast<char *>(other._d.data.ptr)) + 1,
               static_cast<char *>(other._d.data.ptr));
#elif defined(__GNUC__)
      strcpy(static_cast<char *>(_d.data.ptr),
             static_cast<char *>(other._d.data.ptr));
#endif
    } else if (WString == other._d.type) {
      _d.data.ptr =
          new char[wcslen(static_cast<wchar_t *>(other._d.data.ptr)) + 1];
#if defined(_MSC_VER)
      wcscpy_s(static_cast<wchar_t *>(_d.data.ptr),
               wcslen(static_cast<wchar_t *>(other._d.data.ptr)) + 1,
               static_cast<wchar_t *>(other._d.data.ptr));
#elif defined(__GNUC__)
      wcscpy(static_cast<wchar_t *>(_d.data.ptr),
             static_cast<wchar_t *>(other._d.data.ptr));
#endif
    } else
      _d.data = other._d.data;
    this->_d.type = other._d.type;
    this->_d.is_null = other._d.is_null;
    this->_d.is_shared = other._d.is_shared;
    return *this;
  }
  Variant &operator=(Variant &&other) {
    if (this == &other) return *this;
    this->_d = other._d;
    if (String == _d.type || WString == _d.type) {
      this->_d.data.ptr = other._d.data.ptr;
      other.make_invalid();
    }
    return *this;
  }

  Type type() const { return _d.type; }

  bool canConvert(Type type) const {
    if (Invalid == type) return false;
    switch (_d.type) {
      case Invalid:
        return false;
      case Char:
        return WChar != type && WString != type;
      case UChar:
        return WChar != type && WString != type;
      case WChar:
        return Char != type && String != type;
      case Short:
        return true;
      case UShort:
        return true;
      case Int:
        return true;
      case UInt:
        return true;
      case Long:
        return true;
      case ULong:
        return true;
      case LongLong:
        return true;
      case ULongLong:
        return true;
      case Float:
        return Char != type && UChar != type && WChar != type;
      case Double:
        return Char != type && UChar != type && WChar != type;
      case LongDouble:
        return Char != type && UChar != type && WChar != type;
      case String:
        return WString != type;
      case WString:
        return String != type;
      default:
        break;
    }
    return false;
  }

  bool isValid() const { return _d.type != Invalid; }

  std::string toString() const {
    if (!isValid() || WString == _d.type) return "";
    if (String == _d.type) return static_cast<char *>(_d.data.ptr);

    std::stringstream ss;
    try {
      switch (_d.type) {
        case Bool:
          if (_d.data.b)
            ss << "true";
          else
            ss << "false";
          break;
        case Char:
          ss << _d.data.c;
          break;
        case UChar:
          ss << _d.data.uc;
          break;
        case WChar:
          break;
        case Short:
          ss << _d.data.s;
          break;
        case UShort:
          ss << _d.data.us;
          break;
        case Int:
          ss << _d.data.i;
          break;
        case UInt:
          ss << _d.data.ui;
          break;
        case Long:
          ss << _d.data.l;
          break;
        case ULong:
          ss << _d.data.ul;
          break;
        case LongLong:
          ss << _d.data.ll;
          break;
        case ULongLong:
          ss << _d.data.ull;
          break;
        case Float:
          ss << _d.data.f;
          break;
        case Double:
          ss << _d.data.d;
          break;
        case LongDouble:
          ss << _d.data.ld;
          break;
        default:
          break;
      }
    } catch (...) {
      return ss.str();
    }

    return ss.str();
  }

  std::wstring toWString() const {
    if (!isValid() || String == _d.type) return L"";
    if (WString == _d.type) return static_cast<wchar_t *>(_d.data.ptr);

    std::wstringstream wss;
    try {
      switch (_d.type) {
        case Bool:
          if (_d.data.b)
            wss << L"true";
          else
            wss << L"false";
          break;
        case Char:
          wss << _d.data.c;
          break;
        case UChar:
          wss << _d.data.uc;
          break;
        case WChar:
          wss << _d.data.wc;
          break;
        case Short:
          wss << _d.data.s;
          break;
        case UShort:
          wss << _d.data.us;
          break;
        case Int:
          wss << _d.data.i;
          break;
        case UInt:
          wss << _d.data.ui;
          break;
        case Long:
          wss << _d.data.l;
          break;
        case ULong:
          wss << _d.data.ul;
          break;
        case LongLong:
          wss << _d.data.ll;
          break;
        case ULongLong:
          wss << _d.data.ull;
          break;
        case Float:
          wss << _d.data.f;
          break;
        case Double:
          wss << _d.data.d;
          break;
        case LongDouble:
          wss << _d.data.ld;
          break;
        default:
          break;
      }
    } catch (...) {
      return wss.str();
    }

    return wss.str();
  }
  bool toBool() const {
    switch (_d.type) {
      case Bool:
        return _d.data.b;
      case String:
        return (strcmp((char *)_d.data.ptr, "true") == 0);
      case WString:
        return (wcscmp((wchar_t *)_d.data.ptr, L"true") == 0);
      default:
        return numVariantToHelper<bool>(_d.data.b);
    }
  }
  char toChar() const { return numVariantToHelper<char>(_d.data.c); }
  uchar toUchar() const { return numVariantToHelper<uchar>(_d.data.uc); }
  wchar_t toWChar() const { return numVariantToHelper<wchar_t>(_d.data.wc); }
  short toShort() const { return numVariantToHelper<short>(_d.data.s); }
  ushort toUShort() const { return numVariantToHelper<ushort>(_d.data.us); }
  int toInt() const { return numVariantToHelper<int>(_d.data.i); }
  uint toUInt() const { return numVariantToHelper<uint>(_d.data.ui); }
  long toLong() const { return numVariantToHelper<long>(_d.data.l); }
  ulong toULong() const { return numVariantToHelper<ulong>(_d.data.ul); }
  long long toLongLong() const {
    return numVariantToHelper<long long>(_d.data.ll);
  }
  ulonglong toULongLong() const {
    return numVariantToHelper<ulonglong>(_d.data.ull);
  }
  float toFloat() const { return numVariantToHelper<float>(_d.data.f); }
  double toDouble() const { return numVariantToHelper<double>(_d.data.d); }
  long double toLongDouble() const {
    return numVariantToHelper<long double>(_d.data.ld);
  }

 private:
  void make_invalid() {
    _d.type = Invalid;
    _d.is_null = true;
    _d.is_shared = false;
    _d.data.ptr = nullptr;
  }

  template <typename T>
  static T strToNumber(const std::string &str) {
    try {
      switch (typeID<T>()) {
        case Bool:
          return static_cast<T>(stoi(str));
          break;
        case Char:
          return static_cast<T>(stoi(str));
          break;
        case UChar:
          return static_cast<T>(stoul(str));
          break;
        case WChar:
          return static_cast<T>(stoi(str));
          break;
        case Short:
          return static_cast<T>(stoi(str));
          break;
        case UShort:
          return static_cast<T>(stoul(str));
          break;
        case Int:
          return static_cast<T>(stoi(str));
          break;
        case UInt:
          return static_cast<T>(stoul(str));
          break;
        case Long:
          return static_cast<T>(stol(str));
          break;
        case ULong:
          return static_cast<T>(stoul(str));
          break;
        case LongLong:
          return static_cast<T>(stoll(str));
          break;
        case ULongLong:
          return static_cast<T>(stoull(str));
          ;
          break;
        case Float:
          return static_cast<T>(stof(str));
          break;
        case Double:
          return static_cast<T>(stod(str));
          break;
        case LongDouble:
          return static_cast<T>(stold(str));
          break;
        default:
          break;
      }
    } catch (...) {
      return T();
    }

    return T();
  }

  template <typename T>
  static T strToNumber(const std::wstring &wstr) {
    try {
      switch (typeID<T>()) {
        case Bool:
          return static_cast<T>(stoi(wstr));
          break;
        case Char:
          return static_cast<T>(stoi(wstr));
          break;
        case UChar:
          return static_cast<T>(stoul(wstr));
          break;
        case WChar:
          return static_cast<T>(stoi(wstr));
          break;
        case Short:
          return static_cast<T>(stoi(wstr));
          break;
        case UShort:
          return static_cast<T>(stoul(wstr));
          break;
        case Int:
          return static_cast<T>(stoi(wstr));
          break;
        case UInt:
          return static_cast<T>(stoul(wstr));
          break;
        case Long:
          return static_cast<T>(stol(wstr));
          break;
        case ULong:
          return static_cast<T>(stoul(wstr));
          break;
        case LongLong:
          return static_cast<T>(stoll(wstr));
          break;
        case ULongLong:
          return static_cast<T>(stoull(wstr));
          ;
          break;
        case Float:
          return static_cast<T>(stof(wstr));
          break;
        case Double:
          return static_cast<T>(stod(wstr));
          break;
        case LongDouble:
          return static_cast<T>(stold(wstr));
          break;
        default:
          break;
      }
    } catch (const std::exception &) {
      return T();
    }

    return T();
  }

  template <typename T>
  T numVariantToHelper(const T &val) const {
    if (typeID<T>() == _d.type) return val;

    switch (_d.type) {
      case Bool:
        return T(_d.data.b);
        break;
      case Char:
        return T(_d.data.c);
        break;
      case UChar:
        return T(_d.data.uc);
        break;
      case WChar:
        return T(_d.data.wc);
        break;
      case Short:
        return T(_d.data.s);
        break;
      case UShort:
        return T(_d.data.us);
        break;
      case Int:
        return T(_d.data.i);
        break;
      case UInt:
        return T(_d.data.ui);
        break;
      case Long:
        return T(_d.data.l);
        break;
      case ULong:
        return T(_d.data.ui);
        break;
      case LongLong:
        return T(_d.data.ll);
        break;
      case ULongLong:
        return T(_d.data.ull);
        ;
        break;
      case Float:
        return T(_d.data.f);
        break;
      case Double:
        return T(_d.data.d);
        break;
      case LongDouble:
        return T(_d.data.ld);
        break;
      case String:
        return strToNumber<T>(static_cast<char *>(_d.data.ptr));
      case WString:
        return strToNumber<T>(static_cast<wchar_t *>(_d.data.ptr));
      default:
        break;
    }
    return T();
  }

  template <typename T>
  static inline void safe_delete_void_ptr(void *&target) {
    if (target) {
      T temp = static_cast<T>(target);
      delete[] temp;
      temp = nullptr;
      target = nullptr;
    }
  }

 private:
  struct Private {
    inline Private() noexcept : type(Invalid), is_shared(false), is_null(true) {
      data.ptr = nullptr;
    }

    // Internal constructor for initializing variant.
    explicit inline Private(Type variantType) noexcept
        : type(variantType), is_shared(false), is_null(false) {}

    inline Private(const Private &other) noexcept
        : data(other.data),
          type(other.type),
          is_shared(other.is_shared),
          is_null(other.is_null) {}

    union Data {
      bool b;
      char c;
      uchar uc;
      wchar_t wc;
      short s;
      ushort us;
      int i;
      uint ui;
      long l;
      ulong ul;
      long long ll;
      ulonglong ull;
      float f;
      double d;
      long double ld;
      void *ptr;
    } data;

    Type type;
    bool is_shared;
    bool is_null;
  };
  Private _d;
};

#endif  // VARIANT_HPP_
