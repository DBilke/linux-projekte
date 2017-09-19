DELETE DATABASE server;
DELETE DATABASE clients;
CREATE DATABASE server;
CREATE DATABASE clients;
create user 'server'@'localhost' identified by 'server';
grant usage on *.* to 'server'@'localhost' identified by 'server'; 

create user 'client1'@'localhost' identified by 'client1';
grant usage on *.* to 'client1'@'localhost' identified by 'client1'; 

create user 'client2'@'localhost' identified by 'client2';
grant usage on *.* to 'client2'@'localhost' identified by 'client2'; 

grant all privileges on clients.* to 'server'@'localhost';
grant all privileges on server.* to 'server'@'localhost';

grant all privileges on clients.* to 'client1'@'localhost';
grant all privileges on clients.* to 'client2'@'localhost';

flush privileges; 
