You are a senior Python engineer.

Build a **simple CLI-based AI application from scratch** using Python and the OpenAI API.

## Project Structure

Create exactly these files:

```text
simple-ai-cli/
├── user_options.py
├── ai_integration.py
├── .env
└── requirements.txt
```

## Functional Requirements

The CLI must show this menu:

```text
1. Ask Anything to LLM
2. Summarize a long text
3. Translate English to Bengali
4. Interview Prep Question
5. Exit
```

### Option 1 — Ask Anything to LLM

Ask the user:

```text
Enter your question:
```

Send the question to the LLM and print the response.

### Option 2 — Summarize a Long Text

Allow the user to paste multi-line text.

The user should finish input by entering:

```text
END
```

on a separate line.

Send the text to the LLM with instructions to:

- summarize concisely
- preserve important facts
- preserve names and numbers
- preserve decisions and conclusions
- prefer bullet points where appropriate

Print the generated summary.

### Option 3 — Translate English to Bengali

Allow multi-line English input.

The user ends input using:

```text
END
```

Translate the text into natural Bengali.

Requirements:

- preserve meaning
- preserve tone
- avoid unnecessary explanations
- output only the Bengali translation

### Option 4 — Interview Prep Question

Ask:

```text
Enter interview subject:
```

Examples:

```text
Java
Java Concurrency
Kafka
Spring Boot
System Design
Operating Systems
Distributed Systems
LLM
RAG
```

Generate:

- 5 beginner questions
- 5 intermediate questions
- 5 advanced questions

For each question provide:

- Question
- Expected answer
- Important concepts being tested

Keep answers concise and suitable for technical interview preparation.

---

# Architecture

## `user_options.py`

This file must only handle:

- CLI menu
- user input
- multi-line input
- output formatting
- validation
- exception handling

It must NOT contain OpenAI-specific API implementation.

Instantiate and call the AI abstraction from `ai_integration.py`.

Use:

```python
if __name__ == "__main__":
    main()
```

Use Python's `match` statement for menu selection.

---

## `ai_integration.py`

Create a class:

```python
class AIIntegration:
```

It should expose:

```python
ask_llm(question: str) -> str

summarize(text: str) -> str

translate_to_bengali(text: str) -> str

interview_prep(subject: str) -> str
```

Also create one reusable internal method such as:

```python
_generate(system_prompt: str, user_prompt: str) -> str
```

All OpenAI API communication must happen through this method.

Use the official modern OpenAI Python SDK and the **Responses API**.

Conceptually:

```python
from openai import OpenAI

client = OpenAI()

response = client.responses.create(
    model=model,
    instructions=system_prompt,
    input=user_prompt
)

return response.output_text
```

Do not duplicate API-calling code across individual methods.

---

# Configuration

Use `python-dotenv`.

Load configuration from `.env`.

`.env` should contain:

```env
OPENAI_API_KEY=your_openai_api_key_here
OPENAI_MODEL=<configurable-model-name>
```

Do NOT hardcode the API key.

Read configuration using:

```python
os.getenv(...)
```

If `OPENAI_API_KEY` is missing, fail with a clear error message.

The model must be configurable without changing source code.

---

# Error Handling

Handle:

- missing API key
- invalid menu choice
- empty input
- OpenAI API errors
- Ctrl+C / `KeyboardInterrupt`

Do not expose unnecessary stack traces to the CLI user.

Print useful human-readable error messages instead.

---

# Multi-Line Input

Create a reusable helper in `user_options.py`, for example:

```python
def read_long_text() -> str:
```

Behavior:

```text
Paste your text below.
Enter END on a new line when finished.
```

Accumulate lines until:

```text
END
```

is entered.

Return the combined text.

---

# Code Quality

Use:

- Python 3.10+
- type hints
- clean naming
- small functions
- separation of concerns
- reusable methods
- no unnecessary frameworks
- no web UI
- no database
- no async code
- no over-engineering

Keep the implementation suitable for a beginner to understand but structured like a real project.

---

# `requirements.txt`

Include only necessary dependencies, such as:

```text
openai
python-dotenv
```

---

# Expected Run Command

The application must run with:

```bash
pip install -r requirements.txt
python user_options.py
```

---

# Expected CLI Example

```text
==================================================
              SIMPLE AI CLI
==================================================

1. Ask Anything to LLM
2. Summarize a long text
3. Translate English to Bengali
4. Interview Prep Question
5. Exit

Enter your choice: 1

Enter your question: What is optimistic locking?

AI Response:
--------------------------------------------------
...
```

The menu should repeat after every operation until the user chooses `5`.

---

# Deliverables

Return the complete contents of:

1. `user_options.py`
2. `ai_integration.py`
3. `.env`
4. `requirements.txt`

Then provide:

```bash
pip install -r requirements.txt
python user_options.py
```

Do not omit code with placeholders such as:

```python
# implementation here
```

Produce complete runnable code.