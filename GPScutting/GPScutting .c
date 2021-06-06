#include <stdio.h>
#include <math.h>
#include "GPScutting.h"



void GPSModule(void)
{    int i;
    const char comma[2] = ",";
    char c0,GPSValues[100],parseValue[12][20],*token;
   
     int index=0;
	//,longitude=0.0,actlat=0.0
		
    
    c0=UART0_Read();

    //check $GPGLL 
    if(c0=='$')
    {
        char c1 = UART0_Read();

        if(c1=='G')
        {
            char c2= UART0_Read();

            if(c2=='P')
            {
                char c3= UART0_Read();

                if(c3=='G')
                {
                    char c4= UART0_Read();

                    if(c4=='L')
                    {
                        char c5= UART0_Read();

                        if(c5=='L')
                        {
                           
                            char c6= UART0_Read();

                            if(c6==',')
                            {
                              
                                char c7= UART0_Read();

                                while(c7!='*')
                                {
                                  GPSValues[index]=c7;
                                    
                                    c7= UART0_Read();

                                    index++;
                                }

                                index=0;
                                token = strtok(GPSValues, comma);
                                while( token != NULL )
                                {
                                    strcpy(parseValue[index], token);
                                    token = strtok(NULL, comma);
                                    index++;
                                    
                                }
																
								 if ( strcmp( parseValue[5],"A") == 0)
                                {
                                   
                                  
							uart0_write('L');
							uart0_write('A');
							uart0_write('T');
																	
							for(i = 0; i <10; i++)
							  {
							     	latitude[i] = parseValue[0][i];
								uart0_write(parseValue[0][i]);
							  }
																	
							uart0_write(' ');
							uart0_write('L');
							uart0_write('O');
							uart0_write('N');
																	
							for(i = 0; i <10; i++)
						        	{
															
								uart0_write(parseValue[2][i]);
								}
																	
								uart0_write(' ');
																	
															
                              }
                                
                            }
                             
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }			
}
