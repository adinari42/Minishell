/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   samplesplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:01:33 by adinari           #+#    #+#             */
/*   Updated: 2022/12/06 23:20:53 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to split a string into substrings using the given delimiter character
// but only if the delimiter is not between quotation marks of the same type
void split(const char *str, char delimiter, char ***substrings, int *num_substrings) {
    // Count the number of substrings
    *num_substrings = 1;
    char in_quotes = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '"' || str[i] == '\'') {
            if (in_quotes == 0) {
                in_quotes = str[i];
            } else if (in_quotes == str[i]) {
                in_quotes = 0;
            }
        } else if (str[i] == delimiter && in_quotes == 0) {
            (*num_substrings)++;
        }
    }

    // Allocate memory for the substrings
    *substrings = (char**) malloc(*num_substrings * sizeof(char*));
    for (int i = 0; i < *num_substrings; i++) {
        (*substrings)[i] = (char*) malloc(strlen(str) * sizeof(char));
    }

    // Split the string into substrings
    int start_index = 0;
    int substring_index = 0;
    in_quotes = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '"' || str[i] == '\'') {
            if (in_quotes == 0) {
                in_quotes = str[i];
            } else if (in_quotes == str[i]) {
                in_quotes = 0;
            }
        } else if (str[i] == delimiter && in_quotes == 0) {
            strncpy((*substrings)[substring_index], str + start_index, i - start_index);
            (*substrings)[substring_index][i - start_index] = '\0';
            substring_index++;
            start_index = i + 1;
        }
    }

    // Copy the last substring
    strncpy((*substrings)[substring_index], str + start_index, strlen(str) - start_index);
    (*substrings)[substring_index][strlen(str) - start_index] = '\0';
}

int main(int argc, char **argv) {
    char *str = "cat infile \"|\' cat | cat";
    char delimiter = '|';
    char **substrings;
    int num_substrings;

    split(str, delimiter, &substrings, &num_substrings);

    for (int i = 0; i < num_substrings; i++) {
        printf("Substring %d: %s\n", i + 1, substrings[i]);}
}
