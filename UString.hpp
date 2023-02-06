#ifndef USTRING_H_
#define USTRING_H_

#include <regex>
#include <string>
#include <vector>

using std::regex;
using std::smatch;
using std::string;
using std::to_string;
using std::vector;

vector<string> split(const string &data, const string &separator) {
  vector<string> result;
  if (data == "") return result;

  char *thisStr = new char[data.length() + 1];
  char *thisSeparator = new char[separator.length() + 1];

#if defined(_MSC_VER)
  strcpy_s(thisStr, data.length() + 1, data.c_str());
  strcpy_s(thisSeparator, separator.length() + 1, separator.c_str());

  char *next_token = NULL;
  char *token = strtok_s(thisStr, thisSeparator, &next_token);
  while (token) {
    string tempStr = token;
    result.push_back(tempStr);
    token = strtok_s(NULL, thisSeparator, &next_token);
  }
#elif defined(__GNUC__)
  strcpy(thisStr, data.c_str());
  strcpy(thisSeparator, separator.c_str());

  char *token = strtok(thisStr, thisSeparator);
  while (token) {
    string tempStr = token;
    result.push_back(tempStr);
    token = strtok(NULL, thisSeparator);
  }
#endif

  return result;
}

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

  operator string() { return _content; }

  const char *c_str() { return _content.c_str(); }
};

#endif  // USTRING_H_
