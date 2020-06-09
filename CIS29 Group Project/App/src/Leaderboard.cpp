#include "stdafx.h"
#include "Leaderboard.h"
#include "ExceptionHandler.h"

bool Leaderboard::loadFromFile(const std::string& path)
{
	std::ifstream fin;
	fin.open(path);

	if (!fin.is_open())
	{
		return false;
	}

	std::string name;
	float score;
	time_t date;

	while (fin >> name >> score >> date)
	{
		addNewScore(name, score, date);
	}

	fin.close();

	return true;
}

bool Leaderboard::writeToFile(const std::string& path)
{
	std::ofstream fout;
	fout.open(path, std::ios::trunc);
	if (!fout.is_open())
	{
		return false;
	}

	auto it = scores.rbegin();
	for (it = scores.rbegin(); it != scores.rend(); ++it)
	{
		fout << it->getName() << ' ' << it->getScore() << ' ' << it->getDate() << '\n';
	}

	fout.close();

	return true;
}

bool Leaderboard::addNewScore(const std::string& name, const float& score, time_t date)
{
	if (scores.size() < 10)
	{
		scores.emplace_back(Score(name, score, date));
		scores.sort();
		return true;
	}
	else if (score > scores.cbegin()->getScore())
	{
		scores.emplace_back(Score(name, score, date));
		scores.sort();
		scores.pop_front();
		return true;
	}
	return false;
}

bool Leaderboard::checkIfHighScore(const float& score)
{
	return scores.front() < score;
}

void Leaderboard::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	float x = 100.f;
	float y = 100.f;

	renderStates.transform.translate(x, y);
	auto it = scores.crbegin();
	for (it = scores.crbegin(); it != scores.crend(); ++it)
	{
		renderStates.transform.translate(0, 50);
		renderTarget.draw(*it, renderStates);
	}
}