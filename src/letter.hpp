#ifndef LETTER_HPP
#define LETTER_HPP


class Letter
{
private:
    char letter;
    int point;
public:
    Letter(char letter, int point);
    Letter(const Letter &other);
    int getPoint() const;
    char getLetter() const;
    Letter& operator=(const Letter& other);
    
};

inline bool operator==(const Letter& a, const Letter& b) {
    return a.getLetter() == b.getLetter() && a.getPoint() == b.getPoint();
}

#endif // LETTER_HPP
