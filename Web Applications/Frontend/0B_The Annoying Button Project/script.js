// Set up the body styles for centering the button
document.body.style.height = "100vh";
document.body.style.width = "100%";
document.body.style.display = "flex";
document.body.style.justifyContent = "center";
document.body.style.alignItems = "center";
document.body.style.margin = "0"; // Remove margin to avoid any shifting

// Select the button element by its ID or create one dynamically if not present
let button = document.querySelector("#btn");

// or create it if not present 😉
if (!button) {
  button = document.createElement('button');
  button.id = "btn";
  button.textContent = "Hover Me";
  document.body.appendChild(button);
}

// style to the button
button.style.padding = "15px 30px";
button.style.fontSize = "16px";
button.style.border = "2px solid #3498db";
button.style.backgroundColor = "#2980b9";
button.style.color = "#fff";
button.style.borderRadius = "10px";
button.style.cursor = "pointer";
button.style.transition = "0.3s ease";

// Set the position to absolute
button.style.position = "absolute";

// Function to generate a random number between min and max
function getRandomNumber(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

// Add an event listener for mouseover event
button.addEventListener("mouseover", () => {
    // Get viewport size (window dimensions)
    const viewportWidth = window.innerWidth;
    const viewportHeight = window.innerHeight;

    // Get button size
    const buttonWidth = button.offsetWidth;
    const buttonHeight = button.offsetHeight;

    // Generate random positions that ensure the button stays within the viewport
    let randomTop = getRandomNumber(0, viewportHeight - buttonHeight);
    let randomLeft = getRandomNumber(0, viewportWidth - buttonWidth);

    // Apply the positioning styles to the button
    button.style.top = `${randomTop}px`;   // Set random top position
    button.style.left = `${randomLeft}px`; // Set random left position
});




// Select the h1 element
const heading = document.querySelector("h1");

// Apply styles to the h1 element
heading.style.fontFamily = "Arial, sans-serif";
heading.style.fontSize = "2.5rem"; // Adjust the font size
heading.style.color = "#2c3e50"; // Dark blue-gray color
heading.style.textAlign = "center"; // Center the text
heading.style.marginBottom = "20px"; // Space between the h1 and button
heading.style.textShadow = "2px 2px 5px rgba(0, 0, 0, 0.2)"; // Add a subtle shadow effect

// Optionally, you can animate or add more effects based on user interaction
