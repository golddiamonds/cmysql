cmysql
======

C with MySQL

I'm using .cpp files, but am using the "C" connector from Oracle's MySQL page to connect.

- **shell.bat** - I have my CMD prompt setup to run this when starting. This allows me to use "cl" to build my program with Microsoft Visual 2013 from the command line. 
- **build.bat** - This holds the commands needed to build the program. You'll also likely need things like 'libmysql.dll' and 'libmysql.lib' in your src folder. The .dll may need to be in your Windows directory. Play around with this. I'm not 100% sure what's best.
- **mysql_test.cpp** - This holds the C code used to connect to the MySQL database. Right now I have a stock related query in there, but obviously, this can be changed. Also, I'd consider changing the user "root" and the password "drowssap" (password backwards) to something stronger.
