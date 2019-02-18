#include <avr/io.h>
#include <math.h>

int integer(double d)
{
	if(d-floor(d)>0.5)
		return ceil(d);
	else
		return floor(d);
}

int main(void)
{
    long int nx,nxn;
	short msd,lsd,P=0,c=0,i,j,bestC,poor,aut;
	double pf,ang,max,avg,best;
	DDRA=0x00;
	DDRB=DDRC=DDRD=0xFF;
	PORTB=PORTC=PORTD=0x00;
	while(1)
	{
		avg=best=0.0;
		poor=1;
		for (i=0;i<40;i++)
		{
			if (i && i%5==0)
			{
				avg /= 5;
				if(avg>best)
				{
					best=avg;
					bestC=j;
				}
				if(i==5 && avg>0.9)	poor=0;
				avg=0.0;
				if (poor && aut)	PORTC=j=i/5;
			}
			c=max=0;
			while(1)
			{
				nx=nxn=0;
				if (bit_is_set(PINA,0))
				{
					while(bit_is_set(PINA,0));
					while(bit_is_set(PINA,0)==0) nxn++;
					while(bit_is_set(PINA,0))	nx++;
					ang=nx+nxn;
					ang=nx/ang;
					pf=ang*M_PI;
					if(pf>M_PI/2) pf=M_PI/2;
					pf=cos(pf);
					if (pf>max)	max=pf;
					if((++c)==50)
					{
						avg += max;
						P=integer(100*max);
						msd=P/10;
						lsd=P%10;
						if(msd>9)
						{
							msd%=10;
							PORTB |= 0x80;
						}
						else PORTB &= 0x7F;
						PORTD=(msd<<4)|lsd;
						break;
					}
				}
			}
			aut=1;
			if(bit_is_set(PINA,1))
			{
				i=-1;
				PORTC=j=bestC=aut=0;
				avg=best=0.0;
				poor=1;
			}
		}
		PORTC=j=bestC;
	}
}
