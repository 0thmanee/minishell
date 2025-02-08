
<body>
    <h1>Minishell</h1>
    <p>Minishell is a simple shell implementation project written in C. It mimics some of the functionalities of a Unix-like shell, providing a basic command-line interface for users to interact with the operating system.</p>
    <h2>Features</h2>
    <ul>
        <li>Built-in commands include:
            <ul>
                <li><code>env</code>: Displays the environment variables.</li>
                <li><code>cd</code>: Changes the current directory.</li>
                <li><code>echo</code>: Prints arguments to the standard output.</li>
                <li><code>pwd</code>: Prints the current working directory.</li>
                <li><code>unset</code>: Removes environment variables.</li>
                <li><code>exit</code>: Exits the shell.</li>
            </ul>
        </li>
        <li>Command parsing and execution.</li>
        <li>Environment variable handling.</li>
        <li>Support for heredoc (a way to read input from the user until a delimiter is reached).</li>
        <li>Integration with <a href="https://tiswww.case.edu/php/chet/readline/rltop.html">Readline</a> for enhanced user input experience.</li>
    </ul>
    <h2>Installation</h2>
    <ol>
        <li>Clone the repository:
            <pre><code>git clone https://github.com/0thmanee/minishell.git</code></pre>
        </li>
        <li>Navigate to the project directory:
            <pre><code>cd minishell</code></pre>
        </li>
        <li>Compile the project using the provided Makefile:
            <pre><code>make</code></pre>
        </li>
    </ol>
    <h2>Usage</h2>
    <p>After compiling the project, you can run the Minishell executable:</p>
    <pre><code>./minishell</code></pre>
    <p>Once the shell is running, you can start typing commands and see them executed. For example:</p>
    <pre><code>minishell$ echo Hello, world!
Hello, world!
minishell$ pwd
/path/to/current/directory
minishell$ exit
</code></pre>
    <h2>Directory Structure</h2>
    <p>The project is organized into several directories, each containing specific components of the shell:</p>
    <ul>
        <li><code>builtins/</code>: Contains the source files for built-in commands.</li>
        <li><code>parsing/</code>: Contains the source files for command parsing and tokenization.</li>
        <li><code>libft/</code>: Contains utility functions used throughout the project.</li>
        <li><code>execution/</code>: Contains the source files for command execution.</li>
        <li><code>object_files/</code>: Contains the compiled object files.</li>
    </ul>
    <h2>Contributors</h2>
    <ul>
        <li><a href="https://github.com/0thmanee">0thmanee</a></li>
        <li><a href="https://github.com/03yasser">03yasser</a></li>
    </ul>
    <h2>License</h2>
    <p>This project does not have a license.</p>
    <h2>Acknowledgements</h2>
    <p>This project was developed as part of the curriculum at 42 School. Special thanks to the 42 community for their support and resources.</p>
</body>
</html>
