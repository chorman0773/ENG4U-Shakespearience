/*
 * Main.cpp
 *
 *  Created on: Dec. 18, 2018
 *      Author: connor
 */

#include <QuizOption.hpp>
#include <lclib/Random.hpp>
#include <lclib/Text.hpp>
#include <map>

const Question questions[]{
	Question{"Hamlet (the main character) is the _ of Denmark",0,"a) Prince","b) King","c) Fool","d) Who?"},
	Question{"Hamlet's _ killed Hamlet's father (also convientiently named Hamlet)",4,"a) Uncle","b) Father?","c) Mother","d) That's too many Hamlets","e) both a and d"},
	//Question{"This question should not appear.",0,"a) Press to continue"},
	Question{"Polonius's son is ",3,"a) Hamlet","b) Ophelia","c) Chris Columbus","d) Laertes"},
	Question{"Elsinore is",0,"a) The Castle","b) a mis-spelling of Elsa-Noire","c) Somewhere","d) Nowhere"},
	Question{"To be, or ...",2,"a) !2b","b) 2t","c) not to be","d) I'm pretty sure !2b is correct"},
	Question{"When Hamlet is sent to england, he returns to Denmark by",1,"a) Walking","b) Hitching a ride with Pirates","c) Flying with British Airways, because there cheep","d) Is there really a difference between the two"},
	Question{"At the end, when Hamlet lives and takes the throne...",3,"a) He thanks Norway for their assistance","b) He declares war on Norway","c) He has a cup of tea with the English Ambassador","d) Um... Hamlet neither lives nor gets the throne..."},
	Question{"What is the answer",3,"a) Not to be","b) 42","c) What is the Question?","d) Any of the above can be the answer"},
	Question{"(TF) Hamlet wants revenge on his father for killing his uncle and marrying his aunt",1,"True","False"},
	Question{"Both _ and _ are alive at the end of the play",2,"a) Hamlet, Claudius","b) Gertrude, Ophelia","c) Fortinbras, Horatio","d) Everyone"},
	Question{"The Play Hamlet is a ...",2,"a) Play","b) Commedy","c) Work of Art","d) None of the above"},
	Question{"Coincidentally, just as King Hamlet was dead to begin with, so was _.",2,"a) Han Solo","b) Shakespeare","c) Marley","d) Um... ","e) Someone"}
};

int main(){
	auto cmp = [](const Question* a,const Question* b){
		return std::less{}(a->getName(),b->getName());
	};
	std::map<const Question*,select_result_t,std::reference_wrapper<decltype(cmp)>> completedQuestions{std::ref(cmp)};
	const std::size_t maxQs{std::min(std::size(questions),std::size_t{7})};
	int correctAnswers{};
	Random rand{};
	Terminal t{};

	for(std::size_t n =0;n<maxQs;n++){
		std::size_t idx = rand.nextInt(std::size(questions));
		while(completedQuestions.count(questions+idx))
			idx = rand.nextInt(std::size(questions));
		completedQuestions[questions+idx] = questions[idx].select(t);
	}
	for(auto&& a:completedQuestions){
		t.print(a.first->getName(),": ");
		if(a.second)
			t.print("The Correct answer is ",a.second->get());
		else
			t.print("Correct"),correctAnswers++;
		t.print(endline);
	}
	t.print(endline,Color::RED,"You got ",correctAnswers," out of ",int(maxQs)," correct.",endline)
			.print(Color::Reset,"Press any key to exit>",endline).wait();
}



