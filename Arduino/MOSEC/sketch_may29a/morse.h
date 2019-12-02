#ifndef MORSE_H_
#define MORSE_H_

extern char blink300_600_1500flag;//代表是哪种模式灯闪
extern char blink300Completeflg_;//代表完成了一个摩斯码的传递

void morse_initial();
void morse_ledblink();

typedef int bool;
#define false 0
#define true  1

extern char FLAG_creak[30];
/*
 *  FAKE_SPACE IS MARING FOR A SPACE
 */
#define FAKE_SPACE '/'

/*
 * THE CHARACTER THAT BETWEEN TWO MORSE STRING
 */
#define SEPARATOR ' '


typedef struct Morse Morse_t;
struct Morse{
  char c[9];
};



Morse_t *new_morse();

bool str2morse(char m , Morse_t *morse);
bool morse2str(Morse_t *morse, char *ch);

bool mark2morse(char n, Morse_t *morse);
bool morse2mark(Morse_t *morse, char *n);

bool num2morse(char n, Morse_t *morse);
bool morse2num(Morse_t *morse, char *n);

void MorseString2String(char *morse ,char *string, int buf_len);

void String2MorseString(char *string ,char *morse, int buf_len);

void str2lowcase(char *str, char *out, int buf_len);


#endif /* MORSE_H_ */
