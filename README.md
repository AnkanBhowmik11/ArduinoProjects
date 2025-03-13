Concept 
The project aims to create a functional prototype of an Electronic Voting Machine (EVM) using simple components like an Arduino, pushbuttons, LEDs, and a buzzer. The goal is to simulate a secure and user-friendly voting process where:

Voters can cast a single vote for their preferred candidate (A, B, C, or D).

The system ensures fairness by preventing multiple votes per session.

Votes are counted accurately, and the results are displayed after the voting process.

The system locks after counting to avoid further interaction.

This prototype focuses on the core functionalities of real-world EVMs while being simple and educational.

Workflow

Initialization

The Red LED turns ON, indicating that the system is idle.

The system waits for the Reset Button to be pressed to activate voting.

Reset Process

Pressing the Reset Button prepares the system for voting:

Green LED turns ON, indicating that voting is enabled.

Red LED turns OFF.

Voters can now press any one of the candidate buttons (A, B, C, or D) to cast their vote.

Voting Process

Voters press a candidate button to cast their vote:

Voting is disabled immediately after one vote (voteEnabled = false).

The vote count for the selected candidate is incremented.

Red LED turns ON, and Green LED turns OFF to show that voting has concluded.

The buzzer plays a 523 Hz sound for 1 second to confirm the vote.

No additional votes can be cast until the Reset Button is pressed again.

Counting Process

Pressing the Count Button calculates and displays the total votes:

Votes for each candidate are shown in this format:

Candidate A=<votes>/Candidate B=<votes>
Candidate C=<votes>/Candidate D=<votes>
A buzzer sound of 440 Hz plays for 1 second.

The system is locked (votingFinished = true) to prevent further inputs.

Post-Count Lock ("No More Votes!")

Once the Count Button has been pressed:

If any button (Reset, Count, or Candidate buttons) is pressed, the system displays:

No More Votes!
Counting Done.
A buzzer sound of 440 Hz plays for 0.5 seconds to notify the user.

No further interactions are allowed after results are displayed.

How Components Work Together

Pushbuttons:

Candidate Buttons (A, B, C, D): Cast votes for specific candidates.

Reset Button: Enables the system for the next voter.

Count Button: Triggers vote counting and locks the system afterward.

LEDs:

Green LED: Indicates the system is ready for voting.

Red LED: Signals that voting is completed and locked.

Buzzer:

Plays different tones to indicate stages:

523 Hz (1 second): Successful vote confirmation.

440 Hz (1 second): Results announcement.

440 Hz (0.5 seconds): System lock message.

Serial Monitor:

Displays all updates and results for debugging:

Total Votes: <total>
Candidate A=<votes> / B=<votes>
Candidate C=<votes> / D=<votes>
No More Votes! Counting has already been done.**
