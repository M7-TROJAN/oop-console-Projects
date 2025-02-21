function calculateZakat() {
  // Get the values of 'amount' and 'gold-price' from the input fields
  const amount = parseFloat(document.getElementById('amount').value);
  const goldPrice = parseFloat(document.getElementById('gold-price').value);

  // Zakat percentage (2.5% as per Islamic law)
  const zakatPercentage = 2.5 / 100;

  // Validate that both fields have been filled with valid numbers
  if (isNaN(amount) || isNaN(goldPrice)) {
    document.getElementById('result').innerHTML = 'Please fill in both fields with valid numbers.';
    return;
  }

  // Calculate the Nisab (the minimum amount before zakat is due)
  const nisab = goldPrice * 85; // 85 grams of gold

  let resultMessage;

  // If the amount is greater than or equal to the Nisab, zakat is due
  if (amount >= nisab) {
    const zakatAmount = amount * zakatPercentage;
    resultMessage = `Your Zakat amount: ${zakatAmount.toFixed(2)}`;
  } else {
    resultMessage = `No Zakat Required. Your amount is below the Nisab (${nisab.toFixed(2)}).`;
  }

  // Display the result in the 'result' element on the webpage
  document.getElementById('result').innerHTML = resultMessage;
}
