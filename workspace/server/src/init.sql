DROP DATABASE IF EXISTS srv_clnt;
CREATE DATABASE srv_clnt;

create user IF NOT EXISTS  'server'@'localhost' identified by 'server';
grant usage on *.* to 'server'@'localhost' identified by 'server'; 

grant all privileges on srv_clnt.* to 'server'@'localhost';

create user IF NOT EXISTS 'client'@'localhost' identified by 'client';
grant usage on *.* to 'client'@'localhost' identified by 'client'; 

grant all privileges on srv_clnt.* to 'client'@'localhost';

flush privileges; 

USE srv_clnt;
CREATE TABLE IF NOT EXISTS server(Id INT PRIMARY KEY AUTO_INCREMENT, IP VARCHAR(20));
CREATE TABLE IF NOT EXISTS client(Id INT PRIMARY KEY AUTO_INCREMENT, IP VARCHAR(20), MSG VARCHAR(255));

