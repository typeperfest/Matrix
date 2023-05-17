from random import randint

if __name__ == '__main__':
    with open("numbers1.txt", 'w') as file:
        for i in range(1000000):
            file.write(str(randint(-10000, 10000)))
            file.write(' ')
    with open("numbers2.txt", 'w') as file:
        for i in range(1000000):
            file.write(str(randint(-10000, 10000)))
            file.write(' ')