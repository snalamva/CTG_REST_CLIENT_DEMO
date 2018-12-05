#!/bin/ksh
# The script generated complete configuration to use the demo which includes
# creation of CICS region, configuration , compiilation of programs
# CTG side configurtion, 
cd region
# Creating a CICS region named RESTDEMO
cicscp -v create region RESTDEMO 

# Adding Program Definition entry ADDC and GETC for Cheese management
cicsadd -r RESTDEMO -c pd ADDC PathName="`pwd`/ADDC" RSLKey=public
cicsadd -r RESTDEMO -c pd GETC PathName="`pwd`/GETC" RSLKey=public

# Adding TCP-IP Listener and used for ECI TCP-IP based Clients to invoke
# CICS program 
cicsadd -r RESTDEMO -c ld TCPLD TCPAddress=`hostname` TCPService=tcpdemo Protocol=TCP

# Adding IPIC Listener and used for CTG to TXSeries region RESTDEMO communication
# for REST clients
cicsadd -r RESTDEMO -c ld IPIC TCPAddress=`hostname` TCPService=ipicdemo Protocol=IPIC

# The below section adds TCP Port details to /etc/services, recommendation is to add the
#following entry manually to /etc/service files by choosing the PORT number, by default 
#the script adds the following PORTS

#echo "ipicdemo   55567/tcp    # Entry of IPIC listener on CICS region
#ctgwd   55568/tcp       # Entry for CTG HTTP client for REST Clients to send requests
#tcpdemo 55569/tcp       # Entry for TCP-IP Listener used for ECI clients" >> /etc/services 


#Creating DB2 tables and Compiling the programs 
sh -x comp_cics_programs.sh

cicscp -v start region RESTDEMO StartType=cold


# CTG side configuration for ECI clients (optional if you are using ECI client programs)

cd ../eci_samples
sh -x comp_eci.sh

# Backing up ctg.ini file

cp /opt/IBM/cicstg/bin/ctg.ini /opt/IBM/cicstg/bin/ctg.ini.backup

# Generate REST Webservice artifcats add entry to ctg.in file

cd ../rest/addc/ 



ctgassist cheese_add_LS2JS

echo "# To define web service CHEESADD for CICS Program ADDC on CICS region RESTDEMO
SECTION WEBSERVICE = CHEESADD
    URI = /CHEESE/CHEESADD
    BINDFILE=`pwd`/cheese.wsbind
    SERVER=CTGWEBS
ENDSECTION" >> /opt/IBM/cicstg/bin/ctg.ini

cd ../../rest/getc
ctgassist cheese_get_LS2JS



echo "# To define web service CHEESEGET for CICS Program GETC on CICS region  RESTDEMO
SECTION WEBSERVICE = CHEESGET
    URI = /CHEESE/CHEESGET
    BINDFILE=`pwd`/cheese_get.wsbind
    SERVER=CTGWEBS
ENDSECTION" >> /opt/IBM/cicstg/bin/ctg.ini
