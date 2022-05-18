# import numpy as np
from sympy import symbols, Eq, solve

class Rekurzija:

    def __init__(self, prvi_koef, drugi_koef, nulti_clan, prvi_clan):
        self.prvi_koef = prvi_koef
        self.drugi_koef = drugi_koef
        self.nulti_clan = nulti_clan
        self.prvi_clan = prvi_clan


def rekurzije_formula(rekurzija, index):
    a = 1
    b = -rekurzija.prvi_koef
    c = -rekurzija.drugi_koef
    d = b ** 2 - 4 * a * c

    if d == 0:
        prvi = drugi = (-b) / (2 * a)

        x, y = symbols('x y')

        eq1 = Eq(x - rekurzija.nulti_clan, 0)
        eq2 = Eq(x * prvi + y * drugi - rekurzija.prvi_clan, 0)

        sol = solve((eq1, eq2), (x, y))

        rez = sol[x] * prvi ** index + sol[y] * index * drugi ** index

        # A = np.array([[1, 0], [prvi, drugi]])
        # B = np.array([rekurzija.nulti_clan, rekurzija.prvi_clan])
        # C = np.linalg.solve(A,B)

        # return (C[0] * prvi**index + C[1] * index * drugi**index)

    else:
        prvi = (-b - d ** 0.5) / (2 * a)
        drugi = (-b + d ** 0.5) / (2 * a)

        x, y = symbols('x y')

        eq1 = Eq(x + y - rekurzija.nulti_clan, 0)
        eq2 = Eq(x * prvi + y * drugi - rekurzija.prvi_clan, 0)

        sol = solve((eq1, eq2), (x, y))

        rez = sol[x] * prvi ** index + sol[y] * drugi ** index

        # A = np.array([[1, 1],[prvi, drugi]])
        # B = np.array([rekurzija.nulti_clan, rekurzija.prvi_clan])
        # C = np.linalg.solve(A,B)

        # return (C[0] * prvi**index + C[1] * drugi**index)

    return rez


def rekurzije_rekurzivno(rekurzija, index):
    if index == 0:
        return rekurzija.nulti_clan
    elif index == 1:
        return rekurzija.prvi_clan
    else:
        return rekurzija.prvi_koef * rekurzije_rekurzivno(rekurzija, index - 1) + \
               rekurzija.drugi_koef * rekurzije_rekurzivno(rekurzija, index - 2)


def rekurzije_dinamicki(rekurzija, index):

    clanovi = [rekurzija.nulti_clan, rekurzija.prvi_clan]
    for i in range(2, index + 1):
        clanovi.append(rekurzija.prvi_koef * clanovi[i - 1] + rekurzija.drugi_koef * clanovi[i - 2])

    return clanovi[index]


if __name__ == '__main__':
    prvi_koef = float(input("Unesite prvi koeficijent λ_1 rekurzivne relacije: "))
    drugi_koef = float(input("Unesite drugi koeficijent λ_2 rekurzivne relacije: "))
    nulti_clan = float(input("Unesite vrijednost nultog clana niza a_0: "))
    prvi_clan = float(input("Unesite vrijednost prvog clana niza a_0: "))
    trazeni_index = int(input("Unesite redni broj n trazenog clana niza: "))

    rekurzija = Rekurzija(prvi_koef, drugi_koef, nulti_clan, prvi_clan)

    print("Vrijednost n-tog clana niza pomocu formule: " + str(rekurzije_formula(rekurzija, trazeni_index)))
    print("Vrijednost n-tog clana niza dinamicki: " + str(rekurzije_dinamicki(rekurzija, trazeni_index)))
    print("Vrijednost n-tog clana niza iz rekurzije: " + str(rekurzije_rekurzivno(rekurzija, trazeni_index)))
