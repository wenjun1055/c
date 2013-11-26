#include <stdio.h>

double zend_string_to_double(const char *number, int length) /* {{{ */
{
        double divisor = 10.0;
        double result = 0.0;
        double exponent;
        const char *end = number+length;
        const char *digit = number;

                            if (!length) {
                                        return result;
                                            }

                                                while (digit < end) {
                                                            if ((*digit <= '9' && *digit >= '0')) {
                                                                            result *= 10;
                                                                                        result += *digit - '0';
                                                                                                } else if (*digit == '.') {
                                                                                                                digit++;
                                                                                                                            break;
                                                                                                                                    } else if (toupper(*digit) == 'E') {
                                                                                                                                                    exponent = (double) atoi(digit+1);
                                                                                                                                                                result *= pow(10.0, exponent);
                                                                                                                                                                            return result;
                                                                                                                                                                                    } else {
                                                                                                                                                                                                    return result;
                                                                                                                                                                                                            }
                                                                                                                                                                                                                    digit++;
                                                                                                                                                                                                                        }

                                                                                                                                                                                                                            while (digit < end) {
                                                                                                                                                                                                                                        if ((*digit <= '9' && *digit >= '0')) {
                                                                                                                                                                                                                                                        result += (*digit - '0') / divisor;
                                                                                                                                                                                                                                                                    divisor *= 10;
                                                                                                                                                                                                                                                                            } else if (toupper(*digit) == 'E') {
                                                                                                                                                                                                                                                                                            exponent = (double) atoi(digit+1);
                                                                                                                                                                                                                                                                                                        result *= pow(10.0, exponent);
                                                                                                                                                                                                                                                                                                                    return result;
                                                                                                                                                                                                                                                                                                                            } else {
                                                                                                                                                                                                                                                                                                                                            return result;
                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                            digit++;
                                                                                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                                                                                    return result;
}
int main(){
    char *s = "Accept-Language: da, en-gb;q=0.8, en;q=0.7";
    char *qvalue;

    float qval = (float)zend_string_to_double(qvalue + 2, seg - qvalue + 2);
    printf("%f", qval);

    return 0;
}
