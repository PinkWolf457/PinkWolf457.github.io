let Current = 0;
fetch(
  "https://api.coingecko.com/api/v3/coins/markets?vs_currency=usd&order=market_cap_desc&per_page=100&page=1"
)
  .then((response) => response.json())
  .then((data) => {
    const tableBody = document.getElementById("cryptoTableBody");
    data.forEach((coin) => {
      Current = coin.current_price;
      const row = document.createElement("tr");

      const rankCell = document.createElement("td");
      rankCell.innerText = coin.market_cap_rank;

      const coinNameCell = document.createElement("td");
      coinNameCell.innerText = `${coin.name} (${coin.symbol.toUpperCase()})`;
      coinNameCell.onclick = () => openModal(coin.name, coin.current_price);

      const priceCell = document.createElement("td");
      priceCell.innerText = `$${coin.current_price.toFixed(6)}`;

      const marketCapCell = document.createElement("td");
      marketCapCell.innerText = `$${coin.market_cap.toLocaleString()}`;

      const changeCell = document.createElement("td");
      const percentage = coin.price_change_percentage_24h.toFixed(2);
      changeCell.innerText = `${coin.price_change_percentage_24h.toFixed(2)}%`;

      row.appendChild(rankCell);
      row.appendChild(coinNameCell);
      row.appendChild(priceCell);
      row.appendChild(marketCapCell);
      row.appendChild(changeCell);
      if (percentage >= 0) {
        changeCell.classList.add("positive");
      } else {
        changeCell.classList.add("negative");
      }
      tableBody.appendChild(row);
    });
  })
  .catch((error) => console.error("Error fetching data:", error));
function sortTable(n) {
  const table = document.getElementById("cryptoTable");
  const rows = Array.from(table.rows).slice(1);
  let isAscending = table.rows[0].cells[n].classList.toggle("asc");

  rows.sort((rowA, rowB) => {
    const cellA = rowA.cells[n];
    const cellB = rowB.cells[n];

    let valA, valB;
    if (n == 0) {
      valA = parseInt(cellA.innerText);
      valB = parseInt(cellB.innerText);
    } else if (n === 2) {
      valA = parseFloat(cellA.innerText.replace("$", "").replace(",", ""));
      valB = parseFloat(cellB.innerText.replace("$", "").replace(",", ""));
    } else if (n === 4) {
      valA = parseFloat(cellA.innerText.replace("%", ""));
      valB = parseFloat(cellB.innerText.replace("%", ""));
    }

    return isAscending ? valA - valB : valB - valA;
  });
  rows.forEach((row) => table.appendChild(row));
}
function openModal(name, price) {
  document.getElementById("modalCoinName").innerText = name;
  document.getElementById("modalCoinPrice").innerText = `Price: $${price}`;
  document.getElementById("modalCoinPrice").value = price;
  document.getElementById("coinModal").style.display = "block";
}
let profit;
function closeModal() {
  document.getElementById("coinModal").style.display = "none";
  resetCalc();
}
window.onclick = function (event) {
  if (event.target === document.getElementById("coinModal")) closeModal();
};
function resetCalc() {
  document.getElementById("price").value = "";
  document.getElementById("output").innerHTML = "";
  output.classList.remove("positive", "negative");
}
function calcProfit() {
  const buy_price = parseFloat(document.getElementById("price").value);
  const price = parseFloat(document.getElementById("modalCoinPrice").value);
  profit = ((price - buy_price) / buy_price) * 100;
  const output = document.getElementById("output");
  if (profit > 0) {
    output.classList.add("positive");
    output.classList.remove("negative");
  } else {
    output.classList.add("negative");
    output.classList.remove("positive");
  }
  output.innerHTML = profit.toFixed(2) + "%";
  buy_price.value = "";
  profit.value = "";
}
