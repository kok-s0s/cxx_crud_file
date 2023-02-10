#ifndef USTRING_HPP_
#define USTRING_HPP_

#include <regex>
#include <string>
#include <vector>

using std::regex;
using std::smatch;
using std::string;
using std::to_string;
using std::vector;

class UString {
 private:
  string _content;

 public:
  UString(string content) { _content = content; }
  ~UString() {}

  UString args(string substitution) {
    string upToDateContent = "";
    string suffix = "";

    regex percentSign("%([1-9]{1})");

    auto content_begin =
        std::sregex_iterator(_content.begin(), _content.end(), percentSign);
    auto content_end = std::sregex_iterator();

    for (std::sregex_iterator i = content_begin; i != content_end; ++i) {
      smatch match = *i;
      string match_str = match.str();

      int index = match_str[1] - '1';

      if (index == 0)
        upToDateContent += match.prefix().str() + substitution;
      else
        upToDateContent += match.prefix().str() + "%" + std::to_string(index);

      suffix = match.suffix();
    }

    upToDateContent += suffix;

    return UString(upToDateContent);
  }

  UString args(const char *substitution) {
    string upToDateContent = "";
    string suffix = "";

    regex percentSign("%([1-9]{1})");

    auto content_begin =
        std::sregex_iterator(_content.begin(), _content.end(), percentSign);
    auto content_end = std::sregex_iterator();

    for (std::sregex_iterator i = content_begin; i != content_end; ++i) {
      smatch match = *i;
      string match_str = match.str();

      int index = match_str[1] - '1';

      if (index == 0)
        upToDateContent += match.prefix().str() + substitution;
      else
        upToDateContent += match.prefix().str() + "%" + std::to_string(index);

      suffix = match.suffix();
    }

    upToDateContent += suffix;

    return UString(upToDateContent);
  }

  template <typename T>
  UString args(T substitution) {
    string upToDateContent = "";
    string suffix = "";

    regex percentSign("%([1-9]{1})");

    auto content_begin =
        std::sregex_iterator(_content.begin(), _content.end(), percentSign);
    auto content_end = std::sregex_iterator();

    for (std::sregex_iterator i = content_begin; i != content_end; ++i) {
      smatch match = *i;
      string match_str = match.str();

      int index = match_str[1] - '1';

      if (index == 0)
        upToDateContent += match.prefix().str() + std::to_string(substitution);
      else
        upToDateContent += match.prefix().str() + "%" + std::to_string(index);

      suffix = match.suffix();
    }

    upToDateContent += suffix;

    return UString(upToDateContent);
  }

  template <class T, class... Args>
  UString args(T head, Args... rest) {
    UString result(_content);
    result = result.args(head);
    result = result.args(rest...);
    return result;
  }

  friend std::ostream &operator<<(std::ostream &os, const UString &uString) {
    os << uString._content;
    return os;
  }

  operator string() { return _content; }

  const char *c_str() { return _content.c_str(); }
};

#endif  // USTRING_HPP_
