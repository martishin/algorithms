#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
from copy import deepcopy

class Symbol(object):
    def __init__(self, is_terminal, letter):
        self.letter = letter
        self.is_terminal = is_terminal

    def __repr__(self):
        return "(" + self.letter + ")"

    def __eq__(self, other):
        return (
            self.letter == other.letter
            and self.is_terminal == other.is_terminal
        )

class SymbolicString(object):
    def __init__(self):
        self.symbols = []

    def add_symbol(self, symbol):
        self.symbols.append(symbol)

    def fill_from_string(self, string):
        for letter in string:
            self.symbols.append(Symbol(True, letter))

    def __repr__(self):
        new_string = ""
        for letter in self.symbols:
            new_string += '\\n' if letter == "\n" else letter
        return new_string

    def len(self):
        return len(self.symbols)

    def __eq__(self, other):
        if (len(self.symbols) != len(other.symbols)):
            return False

        for index in xrange(len(self.symbols)):
            if (self.symbols[index] != other.symbols[index]):
                return False
        return True


class EarleyParserState(object):
    def __init__(self, letter, symbolic_string, rule_position, word_letter_position,  word_position):
        self.letter = letter
        self.symbolic_string = symbolic_string
        self.rule_position = rule_position
        self.word_letter_position = word_letter_position
        self.word_position = word_position

    def is_full(self):
        return len(self.symbolic_string) == self.rule_position

    def get_next_letter(self):
        return self.symbolic_string[self.rule_position]

    def __repr__(self):
        return "(" + self.letter + "->" + str(self.symbolic_string) + ", " + str(self.rule_position) + ", " + str(self.word_letter_position) + ", " + str(self.word_position) + ")"

    def __eq__(self, other):
        return (
            self.letter == other.letter
            and self.symbolic_string == other.symbolic_string
            and self.rule_position == other.rule_position
            and self.word_letter_position == other.word_letter_position
            and self.word_position == other.word_position
        )

    def __lt__(self, other):
        return (self != other and self.word_position < other.word_position)

    def __hash__(self):
        return hash(str(self))

class Rule(object):
    def __init__(self, letter, symbolic_string):
        self.letter = letter
        self.symbolic_string = symbolic_string

    def get_initial_state(self, word_position):
        return EarleyParserState(self.letter, self.symbolic_string, 0, word_position, word_position)

class EarleyParser(object):
    def __init__(self, rules, target_string):
        self.tmp_states = []
        self.states_to_delete = []
        self.rules_by_letter = {}
        self.target_string = target_string
        self.states_by_word_position = {}
        self.current_word_position = 0
        for rule in rules:
            self.add_state_and_check_added(rule.get_initial_state(self.current_word_position))
            if rule.letter not in self.rules_by_letter:
                self.rules_by_letter[rule.letter] = []
            self.rules_by_letter[rule.letter].append(rule)

        self.appy_states()
        self.parent_states = {}
        self.current_states = {}

    def scan_finished(self, state):
        return state.word_position == len(self.target_string)

    def add_state_and_check_added(self, new_state):
        if new_state.word_position not in self.states_by_word_position:
            self.states_by_word_position[new_state.word_position] = set([])

        if new_state.word_position > self.current_word_position:
            self.tmp_states.append(new_state)
            return False


        if new_state in self.states_by_word_position[new_state.word_position]:
            return False
        else:
            self.tmp_states.append(new_state)
            return True

    def delete_state(self, state):
        self.states_to_delete.append(state)

    def appy_states(self):
        for state in self.tmp_states:
            self.states_by_word_position[state.word_position].add(state)
        self.tmp_states = []
        for state in self.states_to_delete:
            if state in self.states_by_word_position[state.word_position]:
                self.states_by_word_position[state.word_position].remove(state)
        self.states_to_delete = []

    def is_normal_text_symbol(self, letter):
        return (
            letter >= 'a' and letter <= 'z'
            or letter >= 'A' and letter <= 'Z'
            or letter in set(['+', '=', ' ', "\t", "\\", ".", ",", "(", ")", "_", ":"])
        )

    def scan(self):
        new_rules = False
        for state in self.states_by_word_position[self.current_word_position]:
            if state.is_full():
                continue

            if state.word_position >= len(self.target_string):
                continue

            next_symbol = state.get_next_letter()
            target_string_symbol = self.target_string[state.word_position]
            if (
                next_symbol.is_terminal
                and not(self.scan_finished(state))
                and (
                    next_symbol.letter == target_string_symbol
                    or next_symbol.letter == '^' and self.is_normal_text_symbol(target_string_symbol)
                )
            ):
                new_state = deepcopy(state)
                new_state.rule_position += 1
                new_state.word_position += 1
                self.current_states[new_state] = new_state
                self.parent_states[new_state] = [state]
                if self.add_state_and_check_added(new_state):
                    new_rules = True
        return new_rules

    def predict(self):
        new_rules = False
        for state in self.states_by_word_position[self.current_word_position]:
            if state.is_full():
                continue

            next_symbol = state.get_next_letter()
            if (
                not(next_symbol.is_terminal)
            ):
                for rule in self.rules_by_letter[next_symbol.letter]:
                    new_state = rule.get_initial_state(self.current_word_position)
                    self.current_states[new_state] = state
                    self.parent_states[new_state] = []
                    if self.add_state_and_check_added(new_state):
                        new_rules = True
        return new_rules

    def complete(self):
        new_rules = False
        for state in self.states_by_word_position[self.current_word_position]:
            if not(state.is_full()):
                continue

            for other_state in self.states_by_word_position[state.word_letter_position]:
                if other_state.is_full():
                    continue
                next_symbol = other_state.get_next_letter()
                if (
                    not(next_symbol.is_terminal)
                    and next_symbol.letter == state.letter
                    and other_state.word_position == state.word_letter_position
                ):
                    new_state = EarleyParserState(
                        other_state.letter,
                        other_state.symbolic_string,
                        other_state.rule_position + 1,
                        other_state.word_letter_position,
                        state.word_position
                    )
                    self.current_states[new_state] = new_state
                    self.parent_states[new_state] = [other_state, state]
                    if self.add_state_and_check_added(new_state):
                        new_rules = True

        return new_rules


    def fill_parser(self):
        while self.current_word_position < len(self.target_string) + 1:
            if self.current_word_position not in self.states_by_word_position:
                raise Exception(
                    "Parsing failed at symbol "
                    + str(self.current_word_position)
                    + ":"
                    + self.target_string[:self.current_word_position]
                )

            scan_added = self.scan()
            predict_added = self.predict()
            complete_added = self.complete()
            self.appy_states()
            if (
                not(scan_added)
                and not(predict_added)
                and not(complete_added)
            ):
                self.current_word_position += 1
                print "Parsed ", self.current_word_position, " characters"
        last_state = self.get_last_state()
        self.generation_states_list = [last_state]
        self.get_generation_states_list_recursive(last_state)


    def get_last_state(self):
        last_state = None
        for state in self.states_by_word_position[len(self.target_string)]:
            if self.scan_finished(state) and state.is_full() and state.word_letter_position == 0:
                last_state = state

        if not(last_state):
            raise Exception("parsing failed")

        return last_state

    def get_generation_states_list_recursive(self, current_state):
        if current_state not in self.parent_states:
            return
        for state in self.parent_states[current_state]:
            self.generation_states_list.append(state)
            self.get_generation_states_list_recursive(state)


    def get_all_occurencies(self, letter):
        occurences = []
        for state in self.generation_states_list:
            if state.is_full() and state.letter == letter:
                occurences.append(self.target_string[state.word_letter_position : state.word_position])
        return occurences

    # Printing functions
    def get_first(self, pair):
        return pair[0]

    def tree_string(self):
        tree_array = []
        for state_hash in self.current_states:
            state = self.current_states[state_hash]
            parent_states = self.parent_states[state_hash]
            if len(parent_states) > 0:
                tree_array.append([state, parent_states])

        tree_array = sorted(tree_array, key=self.get_first)
        string = ""
        for pair in tree_array:
            state = pair[0]
            parent_states = pair[1]
            string += str(state) + ": " + str(parent_states) + "\n"
        return string


# Test of parser on string aabb
#parser = EarleyParser(
#   [
#       Rule("X", [Symbol(True, "a"), Symbol(False, "X"), Symbol(True, "b")]),
#       Rule("X", []),
#   ],
#   "aabb",
#)
#parser.fill_parser()
#print "Final result"
#print parser.get_all_occurencies("X")

filename = sys.argv[1]
with open(filename, 'r') as handler:
    content = handler.read()
    rules = []

    rules += [
        # T = whole code
        # S = double quoted text
        # Q = sigle quoted text
        # C = whole comment
        # H = part of comment

        Rule("T", [Symbol(True, '"'), Symbol(False, "S"), Symbol(True, '"'), Symbol(False, "T")]),
        Rule("T", [Symbol(True, "'"), Symbol(False, "Q"), Symbol(True, "'"), Symbol(False, "T")]),
        Rule("T", [Symbol(True, '#'), Symbol(False, "C"), Symbol(True, "\n"), Symbol(False, "T")]),
        Rule("T", [Symbol(True, "\n"), Symbol(False, "T")]),
        Rule("T", [Symbol(True, "^"), Symbol(False, "T")]),
        Rule("T", []),

        Rule("S", [Symbol(True, "'"), Symbol(False, "S")]),
        Rule("S", [Symbol(True, '#'), Symbol(False, "S")]),
        Rule("S", [Symbol(True, "\n"), Symbol(False, "S")]),
        Rule("S", [Symbol(True, "^"), Symbol(False, "S")]),
        Rule("S", []),

        Rule("Q", [Symbol(True, '"'), Symbol(False, "Q")]),
        Rule("Q", [Symbol(True, '#'), Symbol(False, "Q")]),
        Rule("Q", [Symbol(True, "\n"), Symbol(False, "Q")]),
        Rule("Q", [Symbol(True, "^"), Symbol(False, "Q")]),
        Rule("Q", []),

        Rule("C", [Symbol(True, "'"), Symbol(False, "H")]),
        Rule("C", [Symbol(True, '"'), Symbol(False, "H")]),
        Rule("C", [Symbol(True, '#'), Symbol(False, "H")]),
        Rule("C", [Symbol(True, "^"), Symbol(False, "H")]),
        Rule("C", []),

        Rule("H", [Symbol(True, '"'), Symbol(False, "H")]),
        Rule("H", [Symbol(True, "'"), Symbol(False, "H")]),
        Rule("H", [Symbol(True, '#'), Symbol(False, "H")]),
        Rule("H", [Symbol(True, "^"), Symbol(False, "H")]),
        Rule("H", []),
    ]

    parser = EarleyParser(
        rules,
        content
    )
    parser.fill_parser()
    print parser.get_all_occurencies("C")
