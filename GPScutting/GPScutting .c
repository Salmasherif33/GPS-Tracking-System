
#include "GPScutting.h"
#include "uart.h"


//function recive GPS readings and extract langitude and latitude 

bool GPSModule(char latitude[] , char langitude [])
{  
    int i;
    const char comma[2] = ",";
    char c0,GPSValues[100],parseValue[12][20],*token;
   
     int index=0;
		    
    c0=UART2_Read();

    //check $GPGLL 
    if(c0=='$')
    {
        char c1 = UART2_Read();

        if(c1=='G')
        {
            char c2= UART2_Read();

            if(c2=='P')
            {
                char c3= UART2_Read();

                if(c3=='G')
                {
                    char c4= UART2_Read();

                    if(c4=='L')
                    {
                        char c5= UART2_Read();

                        if(c5=='L')
                        {
                           
                            char c6= UART2_Read();

                            if(c6==',')
                            {
                              
                                char c7= UART2_Read();

                                while(c7!='*')
                                {
                                  GPSValues[index]=c7;
                                    
                                    c7= UART2_Read();

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
                              			
					for(i = 0; i <10; i++)
					 {
					  latitude[i] = parseValue[0][i];
					  uart0_write(parseValue[0][i]);
					 }
																	
					uart0_write(' ');
																	
					for(i = 0; i <10; i++)
					{							
					  langitude[i] = parseValue[2][i];
					   uart0_write(parseValue[2][i]);
					}
																	
					uart0_write(' ');
				         return true;		
																
                              }
                                
                            }
                             
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }	
 return false;		
}
