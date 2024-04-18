#!/bin/bash

#
#   This script offer three options
#   -> to check for only file descriptors use '-f'
#       ./script.sh -f
#   -> to check for only leaks use '-l'
#       ./script.sh -l
#   -> or run both without using any argument or -a
#       ./script.sh
#

YELLOW=$(tput setaf 3)
RESET=$(tput sgr0)

# Function to check for and handle arguments
check_argument() {
  if [[ "$1" == "-f" ]]; then
    echo "${YELLOW}[./minishell] Opened file descriptors${RESET}"
    lsof -c minishell | tail -n 4
  elif [[ "$1" == "-l" ]]; then
    echo "${YELLOW}[./minishell] Leaks${RESET}"
    leaks minishell
  elif [[ "$1" == "-a" ]]; then
    echo "${YELLOW}[./minishell] Opened file descriptors${RESET}"
    lsof -c minishell | tail -n 4
    echo
    echo "${YELLOW}[./minishell] Leaks${RESET}"
    leaks minishell
  else
    echo "Invalid argument. Usage: ./minishell [-f] [-l]"
  fi
}

# Main loop
while true; do
  # Check if any argument is provided
  if [[ $# -gt 0 ]]; then
    check_argument "$1"  # Pass the first argument to the function
  else
    # No argument, display both information
    echo "${YELLOW}[./minishell] Opened file descriptors${RESET}"
    lsof -c minishell | tail -n 4
    echo
    echo "${YELLOW}[./minishell] Leaks${RESET}"
    leaks minishell
  fi
  echo
  sleep 1.5
done
