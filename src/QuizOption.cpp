/*
 * QuizOption.cpp
 *
 *  Created on: Dec. 18, 2018
 *      Author: connor
 */

#include <QuizOption.hpp>

#include <lclib/Menu.hpp>

#include <algorithm>

select_result_t Question::select(Terminal& t)const{
	Menu menu{this->qName,Color::BLUE};
	std::vector<MenuItem> items{};
	int n{};
	items.reserve(this->opts.size());
	std::transform(begin(opts),end(opts),std::back_inserter(items),[&n](const std::string& s){
		return MenuItem{s,Color::RED,n++};
	});
	for(MenuItem& m:items)
		menu.addItem(m);
	if((n=menu.select(t))==correct)
		return std::nullopt;
	else
		return std::optional{std::cref(opts[correct])};
}

const std::string& Question::getName()const noexcept{
	return qName;
}

