#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <queue>
#include <map>

using namespace std;

class Rule
{
	private:
		bool _value;
		bool _newValue;
		int _state;
		int _nextState;
		int _direction;
	public:
		Rule(bool, int, bool, int, int);
		bool getValue();
		bool getNewValue();
		int getState();
		int getNextState();
		int getDirection();
};

class Tape
{
	private:
		int _headPosition;
		int _state;
		map<int, bool> _tape;
		Tape * _setValues(map<int, bool> *);
	public:
		Tape(int, int, map<int, bool> *);
		static const int STATE_FINISHED = -1;
		Tape * applyRule(Rule *);
		Tape * moveHead(int);
		Tape * setHeadPosition(int);
		int getHeadPosition();
		Tape * setState(int);
		int getState();
		Tape * setValue(bool);
		bool getValue();
		map<int, bool> * getValues();
		void show();
};

class NMT
{
	public:
		NMT(int, int, map<int, bool> *);
		bool start();
		NMT * addRule(Rule *);
	private:
		queue<Tape *> _tapes;
		set<Rule *> _rules;
	protected:
		bool processOneCopy(Tape *);
};


Rule::Rule(bool value, int state, bool newValue, int nextState, int direction)
{
	this->_value = value;
	this->_state = state;
	this->_newValue = newValue;
	this->_nextState = nextState;
	this->_direction = direction;
}

bool Rule::getValue()
{
	return this->_value;
}

bool Rule::getNewValue()
{
	return this->_newValue;
}

int Rule::getState()
{
	return this->_state;
}

int Rule::getNextState()
{
	return this->_nextState;
}

int Rule::getDirection()
{
	return this->_direction;
}

Tape::Tape(int initialState, int initialPosition, map<int,bool> * values = NULL)
{
	this->_setValues(values)
		->setHeadPosition(0)
		->setHeadPosition(initialPosition)
		->setState(initialState);
}

Tape * Tape::_setValues(map<int,bool> * values)
{
	if (values != NULL)
	{
		this->_tape = *values;
	}
	return this;
}

Tape * Tape::applyRule(Rule * rule)
{
	if (this->getState() != rule->getState() || this->getValue() != rule->getValue())
	{
		cerr << "Trying to apply incorrect rule for tape!" << endl;
		return this;
	}

	this->setValue(rule->getNewValue())
		->setState(rule->getNextState())
		->moveHead(rule->getDirection());

	return this;
}

Tape * Tape::setHeadPosition(int position)
{
	this->_headPosition = position;
	return this;
}

Tape * Tape::moveHead(int direction)
{
	if (direction > 0)
	{
		this->_headPosition++;
	} else if (direction < 0)
	{
		this->_headPosition--;
	}
	return this;
}

int Tape::getHeadPosition()
{
	return this->_headPosition;
}

Tape * Tape::setState(int state)
{
	this->_state = state;
	return this;
}

int Tape::getState()
{
	return this->_state;
}

Tape * Tape::setValue(bool value)
{
	this->_tape[this->getHeadPosition()] = value;
	return this;
}

bool Tape::getValue()
{
	if (this->_tape.find(this->getHeadPosition()) != this->_tape.end())
	{
		return this->_tape[this->getHeadPosition()];
	} else
	{
		return false;
	}
}

map<int,bool> * Tape::getValues()
{
	return &this->_tape;
}

void Tape::show()
{
	cout << "Current head position: " << this->getHeadPosition()
		<< ", value: " << this->getValue()
		<< ", state: " << this->getState() << endl;
	cout  << "Positions: ";
	for (int pos = -10; pos <= 10; ++pos)
	{
		printf("%3d", pos);
	}
	cout << endl << "Values:    ";
	for (int pos = -10; pos <= 10; ++pos)
	{
		if (this->_tape.find(pos) == this->_tape.end())
		{
			cout << setw(3) << 0;
		} else
		{
			cout << setw(3) << this->_tape[pos];
		}
	}
	cout << endl;
}

NMT::NMT(int initialState, int initialPosition, map<int,bool> * values = NULL)
{
	Tape * tape = new Tape(initialState, initialPosition, values);

	this->_tapes.push(tape);

	cout << "Created NMT" << endl;
	tape->show();
}

NMT * NMT::addRule(Rule * rule)
{
	this->_rules.insert(rule);
	return this;
}

bool NMT::start()
{
	bool answer = false;
	while (this->_tapes.size() > 0 && answer == false)
	{
		Tape * tape = this->_tapes.front();
		answer = this->processOneCopy(tape);
		this->_tapes.pop();
		cout << " >> Removed tape from queue, tapes count: " << this->_tapes.size() << endl;
	}
	cout << "Finished!" << endl;

	return answer;
}

bool NMT::processOneCopy(Tape * tape)
{
	cout << " >> Processing one NMT copy" << endl;
	tape->show();
	while (tape->getState() != Tape::STATE_FINISHED)
	{
		set<Rule *>::iterator i;
		bool appliedThisTape = false;
		int currentState = tape->getState();
		int currentPosition = tape->getHeadPosition();
		int currentValue = tape->getValue();
		Tape currentTapeCopy = *tape;
//		for (i = this->_rules.begin(); i != this->_rules.end(); ++i)
//		{
//			cout << endl << "Rule: (" <<
//				(*i)->getValue() << ", " <<
//				(*i)->getState() << ", " <<
//				(*i)->getNewValue() << ", " <<
//				(*i)->getNextState() << ", " <<
//				(*i)->getDirection() <<
//				"): " << endl;
//		}
		cout << endl;
		for (i = this->_rules.begin(); i != this->_rules.end(); ++i)
		{
			if ((*i)->getState() == currentTapeCopy.getState() && (*i)->getValue() == currentTapeCopy.getValue())
			{
				if (!appliedThisTape)
				{
					cout << endl << "Applying rule to tape; before applying (" <<
						(*i)->getValue() << ", " <<
						(*i)->getState() << ", " <<
						(*i)->getNewValue() << ", " <<
						(*i)->getNextState() << ", " <<
						(*i)->getDirection() <<
						"): " << endl;
					tape->show();
					tape->applyRule(*i);
					cout << "after: " << endl;
					tape->show();
					cout << endl;
					appliedThisTape = true;
				} else
				{
					Tape * tape = new Tape(currentTapeCopy.getState(), currentTapeCopy.getHeadPosition(), currentTapeCopy.getValues());
					cout << endl << "Applying rule to tape for queue; before applying (" <<
						(*i)->getValue() << ", " <<
						(*i)->getState() << ", " <<
						(*i)->getNewValue() << ", " <<
						(*i)->getNextState() << ", " <<
						(*i)->getDirection() <<
						"): " << endl;
					tape->show();
					tape->applyRule(*i);
					cout << "after: " << endl;
					tape->show();
					this->_tapes.push(tape);
					cout << " >> Added new tape to queue, tapes count: " << this->_tapes.size() << endl;
				}
			}
		}
		if (tape->getValue() == currentValue
			&& tape->getHeadPosition() == currentPosition
			&& tape->getState() == currentState)
		{
			cerr << "Endless loop. No answer this way" << endl;
			return false;
		}
	}
	return tape->getValue();
}



int main()
{
	ifstream input("nmt_input.in");
	if (!input.is_open())
	{
		cerr << "Cannot open input file. Exiting" << endl;
		return 0;
	}
	// reading tape values
	map<int,bool> * values = new map<int,bool>;
	int initialState;
	input >> initialState;
	int initialPosition;
	input >> initialPosition;
	int value;
	int i = 0;
	while (true)
	{
		input >> value;
		if (value == -1)
		{
			break;
		}
		values->insert(make_pair(i++, (bool) value));
	}
	NMT * machine = new NMT(initialState, initialPosition, values);
	while(!input.eof() && input.is_open())
	{
		int value, state, newValue, nextState, direction;
		input >> value >> state >> newValue >> nextState >> direction;
		if (value == -1)
		{
			break;
		}
		machine->addRule(new Rule((bool) value, state, newValue, nextState, direction));
	}
	input.close();

	cout << "The answer is .. " << (machine->start() ? "true" : "false") << endl;

	return 0;
}
