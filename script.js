async function fetchPrices() {
  try {
    const res = await axios.get(
      "https://api.coingecko.com/api/v3/coins/markets",
      {
        params: {
          vs_currency: "usd",
          ids: "bitcoin,ethereum,solana,ripple",
        },
      }
    );

    res.data.forEach((coin) => {
      let prefix = "";
      if (coin.id === "bitcoin") prefix = "btc";
      else if (coin.id === "ethereum") prefix = "eth";
      else if (coin.id === "solana") prefix = "sol";
      else if (coin.id === "ripple") prefix = "xrp";

      const priceId = `${prefix}-price`;
      const changeId = `${prefix}-change`;

      const priceElement = document.getElementById(priceId);
      const changeElement = document.getElementById(changeId);

      priceElement.textContent = `$${coin.current_price.toLocaleString()}`;

      const change = coin.price_change_percentage_24h.toFixed(2);
      changeElement.textContent = `${change}%`;

      if (change >= 0) {
        priceElement.classList.add("positive");
        priceElement.classList.remove("negative");
      } else {
        priceElement.classList.add("negative");
        priceElement.classList.remove("positive");
      }
    });
  } catch (error) {
    console.error("Error fetching prices:", error);
  }
}
fetchPrices();
setInterval(fetchPrices, 60000);
const visibleSections = new Set();

const observer = new IntersectionObserver(
  (entries) => {
    entries.forEach((entry) => {
      if (entry.isIntersecting) {
        visibleSections.add(entry.target);
      } else {
        visibleSections.delete(entry.target);
      }
    });
    const color =
      visibleSections.size > 0
        ? visibleSections.values().next().value.getAttribute("data-color")
        : "#f8f8ff";

    document.body.style.backgroundColor = color;
  },
  {
    threshold: 0.5,
  }
);
document
  .querySelectorAll(".section")
  .forEach((section) => observer.observe(section));

window.onload = function () {
  const ctx = document.getElementById("btcVsUsdChart").getContext("2d");

  new Chart(ctx, {
    type: "line",
    data: {
      labels: ["2021", "2022", "2023", "2024", "2025"],
      datasets: [
        {
          label: "$1000 in USD",
          data: [1000, 1000, 1000, 1000, 1000],
          borderColor: "#252525",
          borderDash: [4, 4],
          pointRadius: 2,
          pointBackgroundColor: "#252525",
          backgroundColor: "transparent",
          fill: false,
          tension: 0.3,
        },
        {
          label: "$1000 in BTC",
          data: [1000, 1800, 1300, 2400, 3000],
          borderColor: "#00ff00",
          pointRadius: 3,
          pointBackgroundColor: "#00ff00",
          backgroundColor: "transparent",
          fill: false,
          tension: 0.3,
        },
      ],
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
      plugins: {
        legend: {
          position: "bottom",
          labels: {
            usePointStyle: true,
            boxWidth: 8,
            boxHeight: 8,
            pointStyle: "circle",
            font: { size: 11 },
            padding: 12,
          },
        },
        title: { display: false },
        subtitle: { display: false },
        tooltip: {
          callbacks: {
            label: function (context) {
              return `${context.dataset.label}: $${context.formattedValue}`;
            },
          },
        },
      },
      scales: {
        y: {
          title: { display: false },
          ticks: {
            callback: function (value) {
              return value === 1000 ? "$1000" : "";
            },
            font: { size: 11 },
            stepSize: 1000,
          },
          grid: {
            drawBorder: false,
            color: "#f0f0f0",
            lineWidth: 0.5,
            drawTicks: false,
          },
        },
        x: {
          title: { display: false },
          ticks: { font: { size: 11 } },
          grid: {
            drawBorder: false,
            color: "#f0f0f0",
          },
        },
      },
    },
  });
};
