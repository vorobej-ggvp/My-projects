from datetime import date
hundred = 100

name = input("Write your name: ")
age  = int(input("Write your age: "))
amount_of_times = int(input("How many times to output: "))
time_left = hundred - age
today = date.today()
curr_year = int(today.strftime("%Y"))
year_hundred = curr_year + time_left
print(amount_of_times * (name + ", you will get 100 years old in " + str(time_left) + ", so it will be " + str(year_hundred) + "\n"))