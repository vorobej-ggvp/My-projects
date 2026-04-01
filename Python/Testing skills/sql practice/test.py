import sqlite3

conn = sqlite3.connect("C:\sqlite\Chinook_Sqlite.sqlite")
cursor = conn.cursor()

cursor.execute("""select distinct * from Track where GenreId='3' and Composer='Black Sabbath' order by Name desc;""")

x = cursor.fetchall()
for i in x:
    print(i)