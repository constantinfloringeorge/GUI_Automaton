#include "Automaton.h"
#include <iostream>
#include <fstream>

void Automaton::adaugaTranzitie(std::pair<char, char> tranzitie, char destinatie)
{
    auto it = Delta.find(tranzitie);
    if (it != Delta.end())
    {
        it->second.emplace_back(destinatie);
    }
    else
    {
        Delta[tranzitie].emplace_back(destinatie);
    }
}

void Automaton::adaugaStare(char stare)
{
	Q.push_back(stare);
}

void Automaton::adaugaSimbol(char simbol)
{
	Sigma.push_back(simbol);
}

void Automaton::seteazaSimbolInitial(char initial)
{
	q0 = initial;
}

std::vector<char> Automaton::getStari()
{
	return this->Q;
}

std::vector<char> Automaton::getSimboluri()
{
	return this->Sigma;
}

std::map<std::pair<char, char>, std::vector<char>> Automaton::getTranzitii()
{
	return this->Delta;
}

char Automaton::getStareInitiala()
{
	return q0;
}

std::vector<char> Automaton::getStariFinale()
{
	return this->F;
}

std::vector<std::pair<int, int>> Automaton::getPozitieStari()
{
    return this->pozitieStari;
}
std::vector<std::pair<char, char>> Automaton::getPozitieTranzitie()
{
    return this->pozitieTranzitie;
}

void Automaton::addPozitieStare(std::pair<int, int> pos)
{
    this->pozitieStari.push_back(pos);
}

void Automaton::addPozitieTranzitie(std::pair<char, char> pos)
{
    this->pozitieTranzitie.push_back(pos);
}


bool Automaton::CheckWord(std::string word, int it, char initialQ)
{
    auto transition = Delta.find({ initialQ,word[it] });
    if (transition != Delta.end())
    {
        for (auto iterator : transition->second)
        {
            for (int i = 0; i < F.size(); i++)
            {
                if (F[i] == iterator && it + 1 == word.size())
                {
                    return true;
                }
            }
            
        }
    }
    if (transition != Delta.end())
    {
        for (auto next : transition->second)
        {
            if (CheckWord(word, it + 1, next))
            {
                return true;
            }
        }
    }
    return false;
}

void Automaton::PrintAutomaton()
{

    std::cout << "Stari: ";
    for (char state : Q) {
        std::cout << state << " ";
    }
    std::cout << std::endl;

    std::cout << "Alfabet: ";
    for (char symbol : Sigma) {
        std::cout << symbol << " ";
    }
    std::cout << std::endl;

    std::cout << "Tranzitii:" << std::endl;
    for (const auto& transition : Delta) {
        std::cout << "(" << transition.first.first << ", " << transition.first.second << ") -> ";
        for (char to : transition.second) {
            std::cout << to << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Stare initiala: " << q0 << std::endl;

    std::cout << "Stari finale: ";
    for (char state : F) {
        std::cout << state << " ";
    }
    std::cout << std::endl;

}
