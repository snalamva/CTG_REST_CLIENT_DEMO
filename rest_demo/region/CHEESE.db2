connect to cicstest
drop table cics.cheese
create table cics.cheese \
  (name char(15) not null, \
   supplier char(30) not null, \
   supplier_address char(30) not null, \
   order_quantity integer not null)

insert into cics.cheese (name, supplier, supplier_address, order_quantity) VALUES ('Stilton', 'Northern Dairies', 'Richmond (Yorks)', 23)

insert into cics.cheese (name, supplier, supplier_address, order_quantity) VALUES ('Wensleydale', 'Northern Dairies', 'Richmond (Yorks)', 14)

insert into cics.cheese (name, supplier, supplier_address, order_quantity) VALUES ('Cheddar', 'Gorge Supplies', 'Wells (Somerset)', 10)

insert into cics.cheese (name, supplier, supplier_address, order_quantity) VALUES ('Brie', 'La Rochelle Importers', 'Dover (Kent)', 45)

insert into cics.cheese (name, supplier, supplier_address, order_quantity) VALUES ('Camembert', 'La Rochelle Importers', 'Dover (Kent)', 33)

insert into cics.cheese (name, supplier, supplier_address, order_quantity) VALUES ('Edam', 'East Anglian Distribution', 'Felixstowe (Suffolk)', 20)

insert into cics.cheese (name, supplier, supplier_address, order_quantity) VALUES ('Cheshire', 'Manchester Dairies', 'Manchester', 18)

insert into cics.cheese (name, supplier, supplier_address, order_quantity) VALUES ('Gouda', 'East Anglian Distribution', 'Felixstowe (Suffolk)', 29)

insert into cics.cheese (name, supplier, supplier_address, order_quantity) VALUES ('Red Leicester', 'Midlands Dairies', 'Leicester (Leics)', 34)

insert into cics.cheese (name, supplier, supplier_address, order_quantity) VALUES ('Boursin', 'La Rochelle Importers', 'Dover (Kent)', 53)

grant all on cics.cheese to public
grant connect on database to public 
quit
