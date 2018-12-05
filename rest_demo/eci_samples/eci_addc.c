
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <cics_eci.h>

/* Structures, defines and macro definitions */

#define ECI_SYNC_SIZE 13

/* Function prototypes */

void Response(short Rc, cics_char_t *Abend);
struct cheese
{
    char    name[15];
    char    supplier[30];
    char    supplier_address[30];
    int     order_quantity;
};

/*  Main Function */

int main(int argc, char *argv[]){

   cics_char_t      progid[4 + 1]  = "ADDC"; /*Program to call                  */
   cics_char_t      chosenServer[CICS_ECI_SYSTEM_MAX +1]; /*Selected servername */
   ECI_PARMS        EciParms;                /*The ECI Parameter block          */
   char             CommArea[ECI_SYNC_SIZE]; /*Commarea for use in ECI calls    */

   char             UserID[8+1] = "";  /*UserID padded to 8 characters    */
   char             PassWd[8+1] = "";  /*Password padded to 8 characters  */

   short            rc;                      /*The return code from the eci call*/
   int              i, choice  =0;
   int              loop       =0;
   struct cheese cheese_details;


   /* Display Banner */

   printf("CICS ECI Client ample\n\n");
   if (argc < 5)
   {
    printf("Usage Erro : Pass all cheese details as Name(string) supplier supplier_address order_quantity(integer)\n");
    printf("Total 4 arguement after program and Use space between each arguments\n");
    printf("example: ./eci_addc Cheese_name1 CheeseSupplier1 SupplierAddress1 200 \n");
    return 2;
   }

   strcpy(cheese_details.name,argv[1]);
   strcpy(cheese_details.supplier, argv[2]);
   strcpy(cheese_details.supplier_address, argv[3]);
   cheese_details.order_quantity = atoi(argv[4]);
      /* Set up the ECI Parameter block */
      memset(chosenServer, '\0', CICS_ECI_SYSTEM_MAX +1);
      strncpy(chosenServer, "CTGTCP", 6);
      memset(&EciParms, 0, sizeof(ECI_PARMS));

      EciParms.eci_version                           = ECI_VERSION_1A;
      EciParms.eci_call_type                         = ECI_SYNC;
      memcpy(&EciParms.eci_program_name, progid,       4);
      memcpy(&EciParms.eci_userid,       UserID,       8);
      memcpy(&EciParms.eci_password,     PassWd,       8);
      memcpy(&EciParms.eci_system_name,  chosenServer, 8);
      EciParms.eci_commarea                          = &cheese_details;
      EciParms.eci_commarea_length                   = sizeof(struct cheese);
      EciParms.eci_extend_mode                       = ECI_NO_EXTEND;
      EciParms.eci_luw_token                         = ECI_LUW_NEW;
   /*   EciParms.eci_timeout                           = 15;*/


      /* Call the chosen server with the given parameters */

      rc = CICS_ExternalCall (&EciParms);
      if (rc == ECI_NO_ERROR) {
         printf("The ECI application to update cheese succesfully updated\n");
      } else {
         Response(rc, EciParms.eci_abend_code);
         return 1;
      }


   return 0;
}


/* Function: Response

   Purpose:  Display the immediate response code from an ECI call */

void Response(short Rc, cics_char_t *Abend)
{
   char *p;
   char *abendString;

   switch (Rc) {
   case ECI_NO_ERROR:                p = "ECI_NO_ERROR               ";break;
   case ECI_ERR_INVALID_DATA_LENGTH: p = "ECI_ERR_INVALID_DATA_LENGTH";break;
   case ECI_ERR_INVALID_EXTEND_MODE: p = "ECI_ERR_INVALID_EXTEND_MODE";break;
   case ECI_ERR_NO_CICS:             p = "ECI_ERR_NO_CICS            ";break;
   case ECI_ERR_CICS_DIED:           p = "ECI_ERR_CICS_DIED          ";break;
   case ECI_ERR_REQUEST_TIMEOUT:     p = "ECI_ERR_REQUEST_TIMEOUT    ";break;
   case ECI_ERR_RESPONSE_TIMEOUT:    p = "ECI_ERR_RESPONSE_TIMEOUT   ";break;
   case ECI_ERR_TRANSACTION_ABEND:   p = "ECI_ERR_TRANSACTION_ABEND  ";break;
   case ECI_ERR_LUW_TOKEN:           p = "ECI_ERR_EXEC_LUW_TOKEN     ";break;
   case ECI_ERR_SYSTEM_ERROR:        p = "ECI_ERR_SYSTEM_ERROR       ";break;
   case ECI_ERR_NULL_WIN_HANDLE:     p = "ECI_ERR_NULL_WIN_HANDLE    ";break;
   case ECI_ERR_NULL_MESSAGE_ID:     p = "ECI_ERR_NULL_MESSAGE_ID    ";break;
   case ECI_ERR_THREAD_CREATE_ERROR: p = "ECI_ERR_THREAD_CREATE_ERROR";break;
   case ECI_ERR_INVALID_CALL_TYPE:   p = "ECI_ERR_INVALID_CALL_TYPE  ";break;
   case ECI_ERR_ALREADY_ACTIVE:      p = "ECI_ERR_ALREADY_ACTIVE     ";break;
   case ECI_ERR_RESOURCE_SHORTAGE:   p = "ECI_ERR_RESOURCE_SHORTAGE  ";break;
   case ECI_ERR_NO_SESSIONS:         p = "ECI_ERR_NO_SESSIONS        ";break;
   case ECI_ERR_NULL_SEM_HANDLE:     p = "ECI_ERR_NULL_SEM_HANDLE    ";break;
   case ECI_ERR_INVALID_DATA_AREA:   p = "ECI_ERR_INVALID_DATA_AREA  ";break;
   case ECI_ERR_INVALID_VERSION:     p = "ECI_ERR_INVALID_VERSION    ";break;
   case ECI_ERR_UNKNOWN_SERVER:      p = "ECI_ERR_UNKNOWN_SERVER     ";break;
   case ECI_ERR_CALL_FROM_CALLBACK:  p = "ECI_ERR_CALL_FROM_CALLBACK ";break;
   case ECI_ERR_MORE_SYSTEMS:        p = "ECI_ERR_MORE_SYSTEMS       ";break;
   case ECI_ERR_NO_SYSTEMS:          p = "ECI_ERR_NO_SYSTEMS         ";break;
   case ECI_ERR_SECURITY_ERROR:      p = "ECI_ERR_SECURITY_ERROR     ";break;
   case ECI_ERR_MAX_SYSTEMS:         p = "ECI_ERR_MAX_SYSTEMS        ";break;
   case ECI_ERR_MAX_SESSIONS:        p = "ECI_ERR_MAX_SESSIONS       ";break;
   case ECI_ERR_ROLLEDBACK:          p = "ECI_ERR_ROLLEDBACK         ";break;
   default:
      {
         p = "!!!Unknown!!!";
         printf("Unknown Return Code : %d\n", Rc);
      }
      break;
   }

   printf("ECI returned: %s\n", p);
   if (Rc != ECI_NO_ERROR) { 
      if (Abend==NULL) {
         abendString="NULL";
      } else {
         abendString=Abend;
      }
      printf("Abend code was \"%4.4s\"\n", abendString);
      printf("An error was encountered. Check COR1 and AOR region logs for more information.\n");
   }

}
