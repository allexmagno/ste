#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#define BAUD 9600
#define FOSC 1843200
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr>>8); //Ajusta a taxa de transmissão
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    //Habilita o transmissor e o receptor
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
    //Ajusta o formato do frame:
    //8 bits de dados e 2 de parada
}

void USART_Transmit(unsigned char data)
{
    while(!( UCSR0A & (1<<UDRE0)));//Espera a limpeza do registr. de transmissão
    UDR0 = data;
}

unsigned char USART_Receive(void)
{
    while(!(UCSR0A & (1<<RXC0))); //Espera o dado ser recebido
    return UDR0;
    //Lê o dado recebido e retorna
}
void USART_Flush(void)

{
    unsigned char dummy;
    while(UCSR0A & (1<<RXC0)) dummy = UDR0;
}

void SPI_Escravo_Inic( )
{
    DDRB = (1<<PB4);//ajusta o pino MISO como saída, demais pinos como entrada
    SPCR = (1<<SPE);//habilita SPI
}

char SPI_Escravo_Recebe( )
{
    while(!(SPSR & (1<<SPIF)));//espera a recepção estar completa
    return SPDR;
    //retorna o registrador de dados
}
int main() {
    USART_Init(MYUBRR);
    SPI_Escravo_Inic();
    /*while(true){
        USART_Transmit('m');
        _delay_ms(1000);
    }*/
    return 0;
}

