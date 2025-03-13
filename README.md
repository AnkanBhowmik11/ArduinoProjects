EVM with Arduino UNO R3


Concept

The project is a simple prototype of an 🗳️ Electronic Voting Machine (EVM) designed to simulate the voting process securely and transparently. It uses components like Arduino, pushbuttons, LEDs, and a buzzer to ensure fairness and accuracy in voting. Voters can cast a single vote, and the system prevents further actions after the votes are counted.

Workflow

📌 Initialization 🟢 The system starts in an idle state, indicated by the red LED being ON. 🟢 It waits for the Reset Button to be pressed, preparing the system for voting.

📌 Reset Process 🟢 When the Reset Button is pressed: ✅ The green LED turns ON, signaling that voting is enabled. ✅ The red LED turns OFF. ✅ The system is now ready, and the voter can press a candidate button to cast their vote.

📌 Voting Process 🟢 The voter selects their preferred candidate by pressing a button (A, B, C, or D). ✅ Once a button is pressed, voting is disabled (voteEnabled = false). ✅ The vote count for the chosen candidate increases by one. ✅ The green LED turns OFF, and the red LED turns ON to indicate the voting session is complete. ✅ A buzzer sounds at 523 Hz for 1 second to confirm the vote.

📌 Counting Process 🟢 Pressing the Count Button totals all votes and announces the results: ✅ Votes are displayed in this format: Candidate A=<votes>/Candidate B=<votes> Candidate C=<votes>/Candidate D=<votes> ✅ A buzzer sounds at 440 Hz for 1 second to notify the user. ✅ The system is locked (votingFinished = true), preventing further interactions.

📌 Post-Count Lock ("No More Votes!") 🟢 If any button (Reset, Count, or Candidate) is pressed after counting: ✅ A message is displayed: "No More Votes! Counting Done." ✅ A buzzer sounds at 440 Hz for 0.5 seconds to notify the user. ✅ The system remains locked until reset manually.

How Components Work Together

🟡 Pushbuttons 🟢 Candidate Buttons: Cast votes for candidates A, B, C, and D. 🟢 Reset Button: Prepares the system for the next voter. 🟢 Count Button: Summarizes the votes and locks the system.

🟡 LEDs 🟢 Green LED: Indicates the system is ready for voting. 🟢 Red LED: Signals that voting has ended.

🟡 Buzzer 🎵 Plays different sounds to provide feedback: ✅ 523 Hz (1 second) confirms successful voting. ✅ 440 Hz (1 second) announces results. ✅ 440 Hz (0.5 seconds) signals system lock.

🟡 Serial Monitor Displays all operations and results for tracking and debugging: ✅ Total Votes: <total> ✅ Candidate A=<votes> / B=<votes> ✅ Candidate C=<votes> / D=<votes> ✅ "No More Votes! Counting Done."
