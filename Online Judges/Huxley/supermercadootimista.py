dia = input()
preco = float(input())
opcao = input()
nome = input()

if (opcao == "ouro" and (dia == "seg" or dia == "ter" or dia == "qua")):
    preco /= 2
elif ((dia == "qui" or dia == "sex") and preco >= 10 and preco <= 100):
    preco /= 3
elif (opcao == "prata" and dia == "sab"):
    preco *= 3
else:
    preco *= 2

print("O preco do produto", nome, "no dia", dia, "eh", round(preco, 2))
