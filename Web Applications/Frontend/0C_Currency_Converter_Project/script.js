
const dollarInput = document.getElementById("dollar");
const poundInput = document.getElementById("pound");
const errorDiv = document.getElementById("error");

let conversionRate = 50; // Default conversion rate

// Function to fetch conversion rates
async function fetchExchangeRates() {
  try {
    const response = await fetch("https://api.exchangerate-api.com/v4/latest/USD"); // USD as base currency
    if (!response.ok) throw new Error("Failed to fetch exchange rates.");
    const data = await response.json();
    conversionRate = data.rates.EGP; // Update conversion rate for EGP
    errorDiv.textContent = ""; // Clear any previous error messages
  } catch (error) {
    errorDiv.textContent = error.message;
  }
}

// Convert from USD to EGP
dollarInput.addEventListener('input', () => {
  const usdValue = parseFloat(dollarInput.value);
  poundInput.value = isNaN(usdValue) ? '' : (usdValue * conversionRate).toFixed(2);
});

// Convert from EGP to USD
poundInput.addEventListener('input', () => {
  const egpValue = parseFloat(poundInput.value);
  dollarInput.value = isNaN(egpValue) ? '' : (egpValue / conversionRate).toFixed(2);
});

fetchExchangeRates();