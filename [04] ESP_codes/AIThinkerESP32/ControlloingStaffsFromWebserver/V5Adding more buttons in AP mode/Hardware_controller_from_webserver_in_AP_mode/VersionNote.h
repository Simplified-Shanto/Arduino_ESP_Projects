
 *   
 * Version: V5 10-29-2023 Adding more buttons in AP mode
 * Modification starts: 10/29/2023 
 * Modifications ends:  
 * Targeted board: Node MCU ESP8266
 * Modified by: Md. Nayeem Islam Shanto (islamshafiul283@gmail.com)
 *
 *How to use? 
 *1. Upload code to ESP8266 board. 
 *2. Enter the IP address from the Serial Monitor to the browser 
 *3. Interact/View the website
 *  
 * 
   In Version 3 and Version 4, we tried to understand the code taken 
   from Random Nerd Tutorials, rearranged it in a way more understandable
   by novice and modified a bit for the purpose of understanding it. 

   

   Goal 1 (Achieved)
   In this version we'll try to add few more buttons thus we can control 
   the Multi Functional Robot Car from web interface. 

   Goal 2. 
   Adding conditions before each Serial print message, thus when the final 
   project runs, the ESP8266 do not send infos like IP address and 
   client request on the serial. Because we'll only send commands in the 
   format "x:y" where x is the name of the command and y is the associated
   value. 

   Goal 3. 
   We moved the code in a separate file which will help manange and update 
   the HTML part very easily. 


   Problem 1. 
   The arduino robot car expects continuous commands to act properly. For 
   example. "f:120." will cause it move for 100-200 millisecond and then 
   stop if another "f:120." is not recieved within a threshold time, it'll 
   stop. But to send multiple commands, we may need to learn functionalities
   like onPress() etc. 
 * 
 * 
 */
