
#include <QVector>


/*
    Набор кубиков 6x6:
    A,A,A,F,R,S
    A,E,A,N,G,N
    A,A,S,E,C,M
    A,A,F,A,R,S
    A,G,N,E,E,E
    A,E,O,I,U,U
    A,B,B,J,O,O
    B,D,E,I,S,X
    D,D,O,N,T,U
    E,E,E,H,N,W
    E,E,H,I,T,T
    E,F,F,K,P,S
    E,I,I,L,S,T
    E,L,R,T,T,Y
    E,I,O,S,S,T
    F,S,U,I,P,R
    G,H,G,R,N,O
    H,H,L,R,D,O
    I,M,N,N,G,E
    I,F,G,R,E,V
    L,D,R,D,H,O
    N,O,N,N,E,E
    O,U,U,E,M,O
    R,T,T,T,L,Y
    S,A,C,O,R,T
    S,E,L,R,U,T
    U,T,O,I,E,S
    W,N,O,T,W,T
    A,E,I,T,M,O
    C,O,U,E,G,I
    D,N,D,H,I,S
    P,A,L,R,I,S
    R,U,N,D,D,S
    W,I,I,I,R,S
    Y,L,E,G,U,B
    Z,V,U,Q,U,N
 */
//TODO: На боковых можно менять буквы
class LettersMap
{
    LettersMap(size_t width, size_t height)
    {
        QVector<QVector<QChar>> m_map(width, QVector<QChar>(height, QChar(' ')));
        QVector<QVector<QChar>> cubes {
                                        {'A','A','A','F','R','S'},
                                        {'A','E','A','N','G','N'},
                                        {'A','A','S','E','C','M'},
                                        {'A','A','F','A','R','S'},
                                        {'A','G','N','E','E','E'},
                                        {'A','E','O','I','U','U'},
                                        {'A','B','B','J','O','O'},
                                        {'B','D','E','I','S','X'},
                                        {'D','D','O','N','T','U'},
                                        {'E','E','E','H','N','W'},
                                        {'E','E','H','I','T','T'},
                                        {'E','F','F','K','P','S'},
                                        {'E','I','I','L','S','T'},
                                        {'E','L','R','T','T','Y'},
                                        {'E','I','O','S','S','T'},
                                        {'F','S','U','I','P','R'},
                                        {'G','H','G','R','N','O'},
                                        {'H','H','L','R','D','O'},
                                        {'I','M','N','N','G','E'},
                                        {'I','F','G','R','E','V'},
                                        {'L','D','R','D','H','O'},
                                        {'N','O','N','N','E','E'},
                                        {'O','U','U','E','M','O'},
                                        {'R','T','T','T','L','Y'},
                                        {'S','A','C','O','R','T'},
                                        {'S','E','L','R','U','T'},
                                        {'U','T','O','I','E','S'},
                                        {'W','N','O','T','W','T'},
                                        {'A','E','I','T','M','O'},
                                        {'C','O','U','E','G','I'},
                                        {'D','N','D','H','I','S'},
                                        {'P','A','L','R','I','S'},
                                        {'R','U','N','D','D','S'},
                                        {'W','I','I','I','R','S'},
                                        {'Y','L','E','G','U','B'},
                                        {'Z','V','U','Q','U','N'}
                                    };

    }
};