CREATE DATABASE IF NOT EXISTS clients;

create user IF NOT EXISTS  'client2'@'localhost' identified by 'client2';
grant usage on *.* to 'client2'@'localhost' identified by 'client2'; 

grant all privileges on clients.* to 'client2'@'localhost';

flush privileges; 

USE clients;
DROP TABLE IF EXISTS client2;


