```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Currency Converter</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            background-color: #f4f4f4;
            margin: 0;
        }
        label {
            margin: 10px 0 5px;
            font-weight: bold;
        }
        input[type="number"] {
            padding: 10px;
            width: 200px;
            border: 1px solid #3498db;
            border-radius: 5px;
            font-size: 16px;
        }
        input[type="number"]:focus {
            border-color: #2980b9;
            outline: none;
        }
        h1 {
            margin-bottom: 20px;
            color: #2c3e50;
        }
        .error {
            color: red;
            margin-top: 10px;
        }
    </style>
</head>
<body>
    <h1>Currency Converter</h1>
    <label for="dollar">USA Dollar (USD)</label>
    <input type="number" placeholder="USD" id="dollar" min="0" step="0.01">

    <label for="pound">Egypt Pound (EGP)</label>
    <input type="number" placeholder="EGP" id="pound" min="0" step="0.01">

    <div id="error" class="error"></div>

    <script>
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
    </script>
</body>
</html>

```