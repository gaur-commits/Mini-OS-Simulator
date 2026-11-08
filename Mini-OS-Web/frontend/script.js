// Get the page elements by their ids
const form = document.getElementById("process-form");
const runButton = document.getElementById("run-simulation-btn");
const tableBody = document.getElementById("process-list-body");
const stateSpan = document.getElementById("simulation-state");
const freeMemorySpan = document.getElementById("free-memory");
const logBox = document.getElementById("execution-log");

// Add one line of text to the log box (red if it is an error)
function addLog(text, isError) {
  const line = document.createElement("p");
  line.className = "log-message";
  if (isError) line.classList.add("log-error");
  line.textContent = text;
  logBox.appendChild(line);
}

// When "Add Process" is clicked
form.addEventListener("submit", async function (event) {
  event.preventDefault(); // stop the page from reloading

  // Read the values the user typed
  const id = document.getElementById("process-id").value;
  const ram = document.getElementById("process-ram").value;
  const ticks = document.getElementById("process-ticks").value;
  const scheduler = document.getElementById("process-scheduler").value;

  // Send them to the C++ server and wait for the answer
  const response = await fetch("/add", {
    method: "POST",
    body: new URLSearchParams({ id, ram, ticks, scheduler })
  });
  const text = await response.text();

  if (response.ok) {
    // C++ accepted it: add a row to the table, update free memory
    tableBody.innerHTML +=
      "<tr><td>" + id + "</td><td>" + ram + "</td><td>" + ticks +
      "</td><td>New</td><td>" + scheduler + "</td></tr>";
    freeMemorySpan.textContent = text;
    form.reset();
  } else {
    // C++ threw an exception: show its message in red
    addLog("Error: " + text, true);
  }
});

// When "Run Simulation" is clicked
runButton.addEventListener("click", async function () {
  const response = await fetch("/run");
  const text = await response.text();

  // Show each line from C++ in the log box
  logBox.innerHTML = "";
  for (const line of text.trim().split("\n")) {
    addLog(line, false);
  }

  // Update the state text and the State column
  stateSpan.textContent = "Running";
  for (const row of tableBody.rows) {
    row.cells[3].textContent = "Running";
  }
});