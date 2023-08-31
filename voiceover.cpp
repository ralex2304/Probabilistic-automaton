#include "voiceover.h"

void speak_add_token(const char* add_token, const bool speak_all) {
    assert(add_token);

    static size_t buf_size = 0;
    static char buf[_TX_BUFSIZE] = "";

    size_t token_len = strlen(add_token);

    if (buf_size + token_len > _TX_BUFSIZE - 1 || buf[buf_size - 1] == '.' || speak_all) {
        buf[buf_size] = '\0';
        txSpeak("<speak version='1.0' xmlns='http://www.w3.org/2001/10/synthesis' xml:lang='EN'>%s</speak>", buf);
        buf_size = 0;
    }

    while (token_len > _TX_BUFSIZE - 1) {
        strncpy(buf, add_token, _TX_BUFSIZE - 1);
        buf[_TX_BUFSIZE - 1] = '\0';
        txSpeak("<speak version='1.0' xmlns='http://www.w3.org/2001/10/synthesis' xml:lang='EN'>%s</speak>", buf);
        add_token += _TX_BUFSIZE - 1;
        token_len -= _TX_BUFSIZE - 1;
    }

    if (token_len > 0) {
        strncpy(buf + buf_size, add_token, token_len);
        buf_size += token_len;
    }
}
