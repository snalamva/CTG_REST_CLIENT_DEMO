#!/bin/ksh
# Script to Compile CICS program used for REST client demo
# Change the DB2 details and run the script to compile the programs

DB2DB=cicstest
DB2USR=cicstest
DB2PWD=cicstest
db2 connect to $DB2DB USER $DB2USR USING $DB2PWD


# Creating Cheese Table in DB2 Database
db2 -f CHEESE.db2
# Runing DB2 prep and compiling programs

db2 prep GETC.sqc collection cics;
db2 grant execute on package cics.GETC to public;
db2 prep ADDC.sqc collection cics;
db2 grant execute on package cics.ADDC to public;
mv GETC.c GETC.ccs
mv ADDC.c ADDC.ccs
export CCFLAGS="-I${DB2DIR}/include"
export   LDFLAGS="-L${DB2DIR}/lib32 -ldb2"
cicstcl -e -d -lC ADDC.ccs
cicstcl -e -d -lC GETC.ccs

rm *.ccs
