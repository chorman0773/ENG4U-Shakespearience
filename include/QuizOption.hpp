/*
 * QuizOption.hpp
 *
 *  Created on: Dec. 18, 2018
 *      Author: connor
 */

#ifndef __INCLUDE_QUIZOPTION_HPP__2018_12_18_13_28_58
#define __INCLUDE_QUIZOPTION_HPP__2018_12_18_13_28_58

#include <string>
#include <vector>
#include <cstddef>
#include <utility>
#include <lclib/Text.hpp>
#include <functional>


typedef std::optional<std::reference_wrapper<const std::string>> select_result_t;

struct Question{
private:
	std::string qName;
	std::size_t correct;
	std::vector<std::string> opts;
public:
	template<typename... Args>
		explicit Question(std::string qName,std::enable_if_t<std::conjunction_v<std::is_convertible<Args,std::string>...>,std::size_t> sz,Args&&... args):
		qName{std::move(qName)},correct{sz},opts{std::initializer_list<std::string>{std::forward<Args>(args)...}}{}

	select_result_t select(Terminal&)const;
	const std::string& getName()const noexcept;
};


#endif /* __INCLUDE_QUIZOPTION_HPP__2018_12_18_13_28_58 */
