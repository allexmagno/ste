#ifndef FILA_H
#define	FILA_H

template <typename T>class Fila {
public:
    Fila(unsigned int N);
    Fila(const Fila<T>& outra);
    ~Fila();
    Fila<T>& operator=(const Fila<T> & outra);
    void enfileira(const T & algo);
    void enfileiraInicio(const T & algo);
    T desenfileira();
    T desenfileiraFim();
    void esvazia();
    const T & frente() const;
    bool vazia() const;
    bool cheia() const;
    unsigned int size() const;
    unsigned int capacidade() const;
private:
    unsigned int cap, itens;
    T * buffer;
    unsigned int inicio, fim, marc;
};
#endif	/* FILA_H */