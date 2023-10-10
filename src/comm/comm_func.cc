
#include <arpa/inet.h>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <locale>
#include <netdb.h>
#include <sstream>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

#include "comm_func.h"

bool isNumric(const char *str_nums) {
    for (const char *p = str_nums; *p; p++) {
        if (*p < '0' || *p > '9') { return false; }
    }

    // 待完善，支持小数、负数。。。

    return true;
}

std::string getTimeStr() {
    char           buff[128];
    std::time_t    t   = std::time(NULL);
    struct std::tm cur = *std::localtime(&t);
    static int state = 1;

    if(++state%2)
        snprintf(buff, sizeof(buff), "%02d%c%02d", cur.tm_hour,':',cur.tm_min);
    else
        snprintf(buff, sizeof(buff), "%02d%c%02d", cur.tm_hour,' ',cur.tm_min);

    // LOGD("getTimeStr()  %s" , buff);
    return std::string(buff);
}

int64_t getTodayTimeSec() {
    std::time_t    t   = std::time(NULL);
    struct std::tm cur = *std::localtime(&t);
    return cur.tm_sec;
}

int64_t getTimeSec() {
    struct timeval _val;
    gettimeofday(&_val, NULL);
    return _val.tv_sec;
}

int64_t getTimeMSec() {
    struct timeval _val;
    gettimeofday(&_val, NULL);
    return (int64_t)_val.tv_sec * 1000 + _val.tv_usec / 1000;
}

std::string getDateTime() {
    char           buffer[128];
    struct timeval _val;

    time_t     now;
    struct tm *tm_now;
    char       datetime[128];

    gettimeofday(&_val, NULL);
    now    = _val.tv_sec;
    tm_now = localtime(&now);
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", tm_now);

    snprintf(buffer, sizeof(buffer), "%s.%03d.%03d", datetime, _val.tv_usec / 1000, _val.tv_usec % 1000);

    return std::string(buffer);
}

int64_t getZeroTime() {
    time_t     t  = time(NULL);
    struct tm *tm = localtime(&t);
    tm->tm_hour   = 0;
    tm->tm_min    = 0;
    tm->tm_sec    = 0;
    return mktime(tm);
}

bool isToday(int64_t sec) {
    int64_t zeroSec = getZeroTime();
    return zeroSec <= sec && sec < zeroSec + DAY_SECONDS;
}

std::string fillLength(int num, int len, std::string pre /* = "0"*/) {
    std::string retString;
    std::string numString = std::to_string(num);
    while (numString.length() + retString.length() < len) { retString.append(pre); }
    retString += numString;
    return retString;
}

std::string fillLength(std::string &str, int len, char end /* = ' '*/) {
    std::string ret = str;
    if (ret.size() < len) ret.append(len - ret.size(), end);
    return ret;
}

void hexdump(const char *label, unsigned char *buf, int len, int width /* = 16*/) {
    int  i, clen;
    char line_buf[512];

    if (width <= 0 || width > 64) { width = 16; }

    LOG(DEBUG) << label << " hex dump:";
    clen = 0;
    for (i = 0; i < len; i++) {
        clen += snprintf(line_buf + clen, sizeof(line_buf) - clen, "%02X ", buf[i]);
        if ((i + 1) % width == 0) {
            LOG(DEBUG) << "  " << line_buf;
            clen = 0;
        }
    }
    if (clen > 0) { LOG(DEBUG) << "  " << line_buf; }
}

std::string hexstr(unsigned char *buf, int len) {
    std::ostringstream oss;
    for (int i = 0; i < len; i++) {
        oss << ' ' << std::hex << std::setfill('0') << std::setw(2) << (int)buf[i];
        if ((i + 1) % 16 == 0) {
            oss << '\n';
        }
    }
    return oss.str();
}

std::string &toUpper(std::string &letter) {
    int         i;
    std::string old = letter;
    letter          = "";
    for (i = 0; i < old.size(); i++) {
        if (old[i] >= 'a' && old[i] <= 'z') {
            letter.append(1, old[i] - 32);
        } else {
            letter.append(1, old[i]);
        }
    }
    return letter;
}

std::string &toLower(std::string &letter) {
    int         i;
    std::string old = letter;
    letter          = "";
    for (i = 0; i < old.size(); i++) {
        if (old[i] >= 'A' && old[i] <= 'Z') {
            letter.append(1, old[i] + 32);
        } else {
            letter.append(1, old[i]);
        }
    }
    return letter;
}

int stringSplit(const std::string &str, std::vector<std::string> &out, char ch /* = ',' */) {
    int    offset = 0;
    size_t pos    = str.find(ch, offset);
    while (pos != std::string::npos) {
        if (offset < pos) out.push_back(str.substr(offset, pos - offset));
        offset = pos + 1;
        pos    = str.find(ch, offset);
    }
    if (offset < str.size()) { out.push_back(str.substr(offset)); }

    return out.size();
}

void timeSet(int year, int month, int day, int hour, int min, int sec) {
    struct timeval tv;
    std::time_t    t;
    struct std::tm cur;

    if (year == 0 && month == 0 && day == 0 && hour == 0 && min == 0 && sec == 0) { return; }

    t   = std::time(NULL);
    cur = *std::localtime(&t);

    if (year > 0)  cur.tm_year = year - 1900;
    if (month > 0) cur.tm_mon  = month - 1;
    if (day > 0)   cur.tm_mday = day;
    if (hour > 0)  cur.tm_hour = hour;
    if (min > 0)   cur.tm_min  = min;
    cur.tm_sec = sec;

    timeSet((int64_t)mktime(&cur));
}

void timeSet(const int64_t &time_sec) {
    struct timeval tv;
    tv.tv_sec  = time_sec;
    tv.tv_usec = 0;    
// #ifndef DEBUG
    LOG(VERBOSE) << "set time " << tv.tv_sec;
    settimeofday(&tv, NULL);
    sysCommand("hwclock --systohc");
// #endif
}

int wordLen(const char *buffer) {
    int         word = 0;
    const char *pos  = buffer;

    while (*pos) {
        if (*pos > 0 && *pos <= 127) {
            // ascii字符
            pos++;
            word++;
        } else {
            // utf-8字符
            pos += 3;
            word++;
        }
    }
    return word;
}

std::string getWord(const char *buffer, int count) {
    std::string words;
    int         wordCount = 0;
    const char *pos       = buffer;
    while (*pos && wordCount < count) {
        if (*pos > 0 && *pos <= 127) {
            wordCount++;
            words.append(1, *(pos++));
        } else {
            wordCount++;
            words.append(1, *(pos++));
            words.append(1, *(pos++));
            words.append(1, *(pos++));
        }
    }
    return words;
}

std::string sysCommand(const std::string &cmd) {
    std::string result;
    char        buffer[128]; // 存储输出数据的缓冲区

    // 执行系统命令，并读取输出数据
    FILE *fp = popen(cmd.c_str(), "r");
    if (fp == NULL) {
        perror("Failed to execute the command.\n");
        return "";
    }

    // 逐行读取输出数据并打印
    bzero(buffer, sizeof(buffer));
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        result.append(buffer);
        bzero(buffer, sizeof(buffer));
    }

    // 关闭文件指针
    pclose(fp);

    return result;
}

std::string getHostIp(const std::string &host) {
    std::string     ip_addr;
    const char *    hostname = host.c_str(); // 要获取IP地址的主机名
    struct addrinfo hints, *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;   // 支持IPv4和IPv6
    hints.ai_socktype = SOCK_STREAM; // 使用TCP协议

    // 解析主机名
    int status = getaddrinfo(hostname, NULL, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return "";
    }

    // 遍历结果列表并打印IP地址
    struct addrinfo *p = result;
    while (p != NULL) {
        void *addr;
        if (p->ai_family == AF_INET) { // IPv4地址
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr                     = &(ipv4->sin_addr);
        } else { // IPv6地址
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr                      = &(ipv6->sin6_addr);
        }

        char ip[INET6_ADDRSTRLEN];
        inet_ntop(p->ai_family, addr, ip, sizeof(ip));
        ip_addr = ip;
        break;

        p = p->ai_next;
    }

    // 释放内存
    freeaddrinfo(result);

    return ip_addr;
}

char *stristr(const char *str1, const char *str2) {
    char *cp = (char *)str1;
    char *s1, *s2;

    if (!*str2) return ((char *)str1);

    while (*cp) {
        s1 = cp;
        s2 = (char *)str2;

        while (*s1 && *s2 && toupper(*s1) == toupper(*s2)) { s1++, s2++; }

        if (!*s2) return (cp);

        cp++;
    }

    return (NULL);
}

/* 编写函数：
 * string& replace_all (string& src, const string& old_value, const string& new_value); 
 * 参数：源字符串src    被替换的子串old_value    替换的子串new_value
 *
 * 功能：将 源串src 中 子串old_value 全部被替换为 new_value
 */ 
std::string& replace_all(std::string& src, const std::string& old_value, const std::string& new_value) {
    // 每次重新定位起始位置，防止上轮替换后的字符串形成新的old_value
    for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length()) {
        if ((pos = src.find(old_value, pos)) != std::string::npos) {
			src.replace(pos, old_value.length(), new_value);
		}
		else break;
	}
	return src;
}
