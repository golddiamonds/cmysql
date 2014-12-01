@echo off

cl -Zi source/mysql_test.cpp /I "C:\Program Files\MySQL\MySQL Connector C 6.1\include" ^
/MD "C:\Program Files\MySQL\MySQL Connector C 6.1\lib\libmysql.lib"
