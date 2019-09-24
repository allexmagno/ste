/* 
 * File:   FILA.h
 * Author: root
 *
 * Created on 21 de Setembro de 2019, 14:27
 */

#ifndef FILA_H
#define	FILA_H
#include <stdlib.h>

template <typename T> class FILA {
public:
    FILA(unsigned int N);
    FILA(const FILA<T>& outra);
    //virtual ~FILA();
    FILA<T>& operator=(const FILA<T> & outra);
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


template <typename T> FILA<T>::FILA(unsigned int N):cap(N) {
    // inicia os atributos da Fila: inicialmente
    // ela está vazia

    inicio = 0;
    fim = 0;
    itens = 0;
 
    // aloca memória para guardar "capacidade" dados do tipo "T"
    //buffer = new T[cap];
    buffer = (T*) malloc(cap*sizeof(T));

}

template <typename T> FILA<T>::FILA(const FILA& outra) {
  itens = outra.itens;
  cap = outra.cap;
  inicio = outra.inicio;


  buffer = new T[cap];

  for(int j = 0; j < cap; j++){
     int pos = (outra.inicio + j) % outra.cap;
     buffer[j] = outra.buffer[pos];
  }
  fim = outra.fim;
}

template <typename T> FILA<T>& FILA<T>::operator=(const FILA& outra) {
  itens = outra.itens;
  if(cap < outra.cap) cap = outra.cap;
  inicio = 0;
  fim = cap;

  delete[] buffer;

  buffer = new T[cap];

  for(int j = 0; j < cap; j++){
     int pos = (outra.inicio + j) % outra.cap;
     buffer[j] = outra.buffer[pos];
  }
  return *this;
}

template <typename T> void FILA<T>::enfileira(const T& algo) {
  if(!cheia()) {// throw "Fila cheia!";
 
  buffer[fim] = algo;
  fim = (fim + 1) % cap;
  itens++;
  }
}

template <typename T> void FILA<T>::enfileiraInicio(const T & algo) {
    if(cheia()) throw "Fila cheia";
    if(inicio == 0){
        buffer[cap-1] = algo;
        inicio = cap-1;
        itens++;
    }else{
        inicio--;
        buffer[inicio] = algo;
        itens++;
    }
}


template <typename T> T FILA<T>::desenfileira() {
    if (itens == 0) //throw "Fila vazia";
        return 0;
    if(cap > 0){
        int pos = inicio;
        if(inicio == cap-1) {
            inicio = 0;
        }
        else{
            inicio++;
        } 
        itens--;
        return buffer[pos];
    }
}

template <typename T> T FILA<T>::desenfileiraFim() {
    if (itens == 0) throw "Fila vazia";
    if(cap > 0){
    if(fim == 0)fim = cap-1;
    else fim--;
    itens--;

  return buffer[fim]; 
    }
}
template <typename T> const T & FILA<T>::frente() const {
    if(vazia()) throw "Fila Vazia!";
    return buffer[inicio];
}

template <typename T> bool FILA<T>::vazia() const {
    return itens == 0;
}

template <typename T> bool FILA<T>::cheia() const {
     return itens == cap;
}

template <typename T> unsigned int FILA<T>::capacidade() const {
    return cap;
}

template <typename T> unsigned int FILA<T>::size() const {
    return itens;
}
template <typename T> void FILA<T>::esvazia(){
    itens = 0;
}
/*template <typename T> FILA<T>::~FILA() {
    delete[] buffer;
}*/

