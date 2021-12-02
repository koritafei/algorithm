#include <string>

const int   CHN_NUM_CHAR_COUNT = 10;
const char *chnNumChar[CHN_NUM_CHAR_COUNT] =
    {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
const char *chnUnitSection[] = {"", "万", "亿", "万亿"};
const char *chnUnitChar[]    = {"", "十", "百", "千"};

void sectionToChinese(unsigned int section, std::string &chnStr) {
  std::string strIns;
  int         unitPos = 0;
  bool        zero    = true;
  while (section > 0) {
    int v = section % 10;

    if (0 == v) {
      if (!zero) {
        zero = true;  // 确保多个0，只补一个中文0
        chnStr.insert(0, chnNumChar[v]);
      }
    } else {
      zero   = false;                     // 至少有一个数字不是
      strIns = chnNumChar[v];             // 此位对应的中文数字
      strIns += chnUnitSection[unitPos];  // 此位对应的中文权位
      chnStr.insert(0, strIns);
    }

    unitPos++;
    section /= 10;
  }
}

void NumberToChinese(unsigned int num, std::string &chnStr) {
  int         unitPos = 0;
  std::string strIns;
  bool        needZero = false;

  while (num > 0) {
    unsigned int section = num % 10000;
    if (needZero) {
      chnStr.insert(0, chnNumChar[0]);
    }

    sectionToChinese(section, chnStr);
    // 是否需要权位
    strIns += (section != 0) ? chnUnitSection[unitPos] : chnUnitSection[0];
    chnStr.insert(0, strIns);
    // 千位是0，需要在下一个权位补0
    needZero = (section < 1000) && (section > 0);
    num /= 10000;
    unitPos++;
  }
}

typedef struct {
  const char *name;     // 中文权位名称
  int         value;    // 10的倍数
  bool        secUnit;  // 是否权位
} CHN_NUME_VALUE;

CHN_NUME_VALUE chnValuePair[] = {{"十", 10, false},
                                 {"百", 100, false},
                                 {"千", 1000, false},
                                 {"万", 10000, true},
                                 {"亿", 1000000000, true}};
