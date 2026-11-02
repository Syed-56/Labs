const fs = require('fs');
const {
  Document, Packer, Paragraph, TextRun, HeadingLevel, AlignmentType, Header, Footer,
  PageNumber, LevelFormat, Table, TableRow, TableCell, WidthType, BorderStyle,
  ShadingType, VerticalAlign
} = require('docx');

const FONT = 'Times New Roman';
const MONO = 'Courier New';

// ---------- inline markup: **bold**, _{sub}, ^{sup} ----------
function runs(text, base = {}) {
  const out = [];
  let bold = false;
  const tokens = text.split(/(\*\*|_\{[^}]*\}|\^\{[^}]*\})/).filter(t => t !== '');
  for (const t of tokens) {
    if (t === '**') { bold = !bold; continue; }
    const o = { text: t, font: FONT, bold: bold || base.bold || undefined, size: base.size, italics: base.italics, color: base.color };
    if (t.startsWith('_{')) { o.text = t.slice(2, -1); o.subScript = true; }
    else if (t.startsWith('^{')) { o.text = t.slice(2, -1); o.superScript = true; }
    out.push(new TextRun(o));
  }
  return out;
}

// ---------- block helpers ----------
const title = t => new Paragraph({ heading: HeadingLevel.TITLE, children: [new TextRun({ text: t, font: FONT })] });
const h1 = t => new Paragraph({ heading: HeadingLevel.HEADING_1, children: [new TextRun({ text: t, font: FONT })] });
const h2 = t => new Paragraph({ heading: HeadingLevel.HEADING_2, children: [new TextRun({ text: t, font: FONT })] });
const p = t => new Paragraph({ spacing: { after: 80 }, children: runs(t) });
const bullet = (t, level = 0) => new Paragraph({ numbering: { reference: 'bullets', level }, spacing: { after: 60 }, children: runs(t) });
const detail = items => [
  new Paragraph({ spacing: { before: 80, after: 40 }, keepNext: true, children: runs('**Detailed Explanation:**') }),
  ...items.map(t => bullet(t))
];
const selfTest = (q, a) => [
  new Paragraph({ spacing: { before: 160, after: 40 }, keepNext: true, children: runs('**Self Test:** ' + q) }),
  new Paragraph({ spacing: { after: 120 }, children: runs('**Answer:** ' + a) })
];
const code = lines => lines.map((l, i) => new Paragraph({
  spacing: { before: i === 0 ? 80 : 0, after: i === lines.length - 1 ? 120 : 0, line: 240 },
  shading: { type: ShadingType.CLEAR, fill: 'F2F2F2', color: 'auto' },
  indent: { left: 360 },
  children: [new TextRun({ text: l, font: MONO, size: 21 })]
}));
const img = (slide, desc) => new Paragraph({
  alignment: AlignmentType.CENTER,
  spacing: { before: 120, after: 120 },
  children: [new TextRun({ text: `[ IMAGE | ${slide}: ${desc} ]`, italics: true, size: 22, color: '0000FF', highlight: 'lightGray', font: FONT })]
});
const spacer = () => new Paragraph({ spacing: { after: 120 }, children: [] });

// ---------- tables ----------
const thin = { style: BorderStyle.SINGLE, size: 4, color: '000000' };
const borders = { top: thin, bottom: thin, left: thin, right: thin };
function cell(raw, w, { header = false, center = false, size = 22 } = {}) {
  const c = typeof raw === 'object' ? raw : { t: raw };
  let shading;
  if (header) shading = { type: ShadingType.CLEAR, fill: 'D9D9D9', color: 'auto' };
  else if (c.hl) shading = { type: ShadingType.CLEAR, fill: 'FFF2CC', color: 'auto' };
  return new TableCell({
    width: { size: w, type: WidthType.DXA },
    borders,
    shading,
    margins: { top: 50, bottom: 50, left: 90, right: 90 },
    verticalAlign: VerticalAlign.CENTER,
    children: [new Paragraph({
      alignment: center ? AlignmentType.CENTER : AlignmentType.LEFT,
      spacing: { after: 0, line: 240 },
      children: runs(c.t, { bold: header || c.bold, size })
    })]
  });
}
function tbl(widths, rows, { size = 22, numeric = false } = {}) {
  const total = widths.reduce((a, b) => a + b, 0);
  return [
    new Table({
      width: { size: total, type: WidthType.DXA },
      columnWidths: widths,
      rows: rows.map((r, ri) => new TableRow({
        tableHeader: ri === 0,
        cantSplit: true,
        children: r.map((c, ci) => cell(c, widths[ci], { header: ri === 0, center: numeric && (ci > 0 || ri === 0), size }))
      }))
    }),
    spacer()
  ];
}
// numeric DP table helper: first column label, then numbers
const dpTable = (labelW, colW, headers, rows, size = 20) =>
  tbl([labelW, ...headers.slice(1).map(() => colW)], [headers, ...rows], { size, numeric: true });

// ---------- content ----------
const body = [];
const add = (...x) => x.flat().forEach(i => body.push(i));

const DP = 'DP PDF', DP2 = 'DP-2 PDF', KN = 'Knapsack PDF';

add(title('DYNAMIC PROGRAMMING'));

// =====================================================================
add(h1('INTRODUCTION TO DYNAMIC PROGRAMMING'));
add(h2('WHAT IS DYNAMIC PROGRAMMING'));
add(
  bullet(`**Dynamic Programming (DP)** – a general algorithm design technique for solving problems defined by recurrences with overlapping subproblems.`),
  bullet(`Typically applies to **optimization problems**, which can have many possible solutions. Each solution has a value and we want a solution with the optimal (minimum or maximum) value.`),
  bullet(`Such a solution is called **an** optimal solution, not **the** optimal solution, since several solutions may reach the optimal value.`),
  bullet(`Invented by the American mathematician Richard Bellman in the 1950s to solve optimization problems, and later adopted by computer science.`),
  bullet(`"Programming" here means "planning" and refers to a **tabular method**, not writing code.`),
  bullet(`**Main idea:**`),
  bullet(`Set up a recurrence relating the solution of a larger instance to solutions of smaller instances.`, 1),
  bullet(`Solve each smaller instance only once.`, 1),
  bullet(`Record the solutions in a table and reuse them instead of recomputing.`, 1)
);

add(h2('DIVIDE AND CONQUER VS DP'));
add(
  bullet(`**Divide-and-conquer** – solves a problem in three steps:`),
  bullet(`**Divide** – split a large input into two or more disjoint subproblems.`, 1),
  bullet(`**Conquer** – solve the subproblems recursively.`, 1),
  bullet(`**Combine** – merge the subproblem solutions into a solution of the original problem.`, 1),
  bullet(`**Eg:** MergeSort. Its subproblems are independent and all different, so no work is repeated.`),
  img(`Slide 5 (${DP2})`, `MergeSort pseudocode (Merge-Sort(A, p, r)) and the splitting tree of the sorted array 17, 24, 30, 45, 50, 63, 85, 96 showing independent subproblems`),
  bullet(`**Dynamic programming** is a way of improving inefficient divide-and-conquer algorithms. It applies when subproblems **overlap**, that is, when subproblems share sub-subproblems.`),
  bullet(`"Inefficient" means the same recursive call is made over and over, so divide-and-conquer does more work than necessary.`),
  bullet(`DP solves each subproblem once, stores the answer in a table the first time it is computed and never recomputes it.`)
);
add(tbl([1800, 3613, 3613], [
  ['Aspect', 'Divide and Conquer', 'Dynamic Programming'],
  ['Subproblems', 'Partitions the problem into independent smaller subproblems', 'Partitions the problem into overlapping subproblems'],
  ['Storing results', 'Does not store solutions of subproblems, so identical subproblems may arise and the same computation is repeated', 'Stores solutions of subproblems, so the same quantity is never calculated twice'],
  ['Direction', 'Top-down: moves from the initial instance down to the smallest sub-instances via intermediate sub-instances', 'Bottom-up: smallest subproblems are solved first and their results build solutions to progressively larger sub-instances'],
  ['Examples', 'MergeSort', 'Fibonacci, 0/1 Knapsack, LCS, Matrix Chain Multiplication']
]));
add(img(`Slide 8 (${DP2})`, `Two-column comparison table of Divide and Conquer vs Dynamic Programming (three numbered rows)`));

add(h2('ELEMENTS OF DP'));
add(
  p(`A problem suits DP when it has these characteristics:`),
  bullet(`**Simple subproblems** – the original problem can be broken into smaller subproblems that have the same structure.`),
  bullet(`**Optimal substructure** – the optimal solution to the problem contains optimal solutions to its subproblems.`),
  bullet(`**Overlapping subproblems** – in some places the same subproblem is solved more than once.`)
);

add(h2('PRINCIPLE OF OPTIMALITY'));
add(
  bullet(`DP works on the **principle of optimality**.`),
  bullet(`It states that in an optimal sequence of decisions or choices, each subsequence must also be optimal.`)
);

add(h2('STEPS TO DESIGN A DP ALGORITHM'));
add(
  bullet(`**Step 1:** Characterize the optimal substructure.`),
  bullet(`**Step 2:** Recursively define the value of an optimal solution.`),
  bullet(`**Step 3:** Compute the value bottom up.`),
  bullet(`**Step 4:** (if needed) Construct an optimal solution.`)
);

add(h2('DP APPROACHES: MEMOIZATION AND TABULATION'));
add(tbl([1800, 3613, 3613], [
  ['Aspect', 'Memoization', 'Tabulation'],
  ['Direction', 'Top-down', 'Bottom-up'],
  ['Starting point', 'Starts from the original problem (e.g. fib(5)) and recurses down to the base cases', 'Starts from the smallest case (index 0) and builds up to n'],
  ['Style', 'Recursive. A table initialised to -1 is checked before every call', 'Iterative. A loop fills the table using base cases and the recurrence'],
  ['Stored result', 'Saved the first time a subproblem is computed, returned in constant time afterwards', 'Every table entry is computed in order, smaller entries first']
]));
add(img(`Slide 10 (${DP2})`, `Tree diagram: Dynamic Programming splits into Memoization (top-down approach) and Tabulation (bottom-up approach)`));
add(selfTest(
  `MergeSort has optimal substructure and is defined recursively. Would storing subproblem results in a table make it faster? Why or why not?`,
  `No. Its subproblems are independent and all different, so no subproblem is ever solved twice and a table would only waste memory. DP helps only when subproblems overlap.`
));

// =====================================================================
add(h1('EXAMPLE: FIBONACCI NUMBERS'));
add(h2('PLAIN RECURSION (DIVIDE AND CONQUER)'));
add(
  bullet(`**Definition** – F(0) = 0, F(1) = 1 and F(n) = F(n-1) + F(n-2) for n ≥ 2.`),
  bullet(`Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...`),
  bullet(`The straightforward recursive procedure is slow.`)
);
add(code([
  'int fib(int n) {',
  '    if (n <= 1)',
  '        return n;',
  '    else',
  '        return fib(n-2) + fib(n-1);',
  '}'
]));
add(
  bullet(`Recurrence of the running time: T(n) = T(n-1) + T(n-2) + 1. Taking an upper bound (both calls treated as T(n-1)) gives **T(n) = 2T(n-1) + 1**, so the time is **O(2^{n})**.`),
  bullet(`In the recursion tree the same calls (fib(3), fib(2), fib(1), fib(0)) appear again and again. We keep calculating the same value over and over.`)
);
add(img(`Slide 4 (${DP})`, `Handwritten notes: Fibonacci definition, the recursive fib code and its recurrence T(n) = 2T(n-1) + 1 giving O(2^n)`));
add(img(`Slide 5 (${DP})`, `Handwritten recursion tree of fib(5) with repeated calls circled (left) and the memoized version with array F of -1 values being filled (right)`));
add(img(`Slide 15 (${DP2})`, `Recursion tree of F(6) = 8 with the repeated subtrees shaded grey`));

add(h2('MEMOIZATION (TOP-DOWN)'));
add(
  bullet(`Create an array F[0..n] with every entry initially **-1** (meaning "not computed yet").`),
  bullet(`Before computing fib(k), check F[k]. If it is not -1, return it immediately. Otherwise compute it, store it and return it.`),
  bullet(`Each fib(k) is now computed only once, so the tree collapses to about n calls and the time is **O(n)**.`)
);
add(code([
  'int fib(int n) {',
  '    if (n <= 1) return n;',
  '    if (F[n] != -1) return F[n];',
  '    F[n] = fib(n-2) + fib(n-1);',
  '    return F[n];',
  '}'
]));

add(h2('TABULATION (BOTTOM-UP)'));
add(
  bullet(`Compute the solution bottom up, starting from index 0 and going to n, remembering solutions of already solved subproblems.`),
  bullet(`Fn is calculated in **linear time**.`),
  bullet(`Only two values need to be remembered at any time (the previous two).`)
);
add(code([
  'int fib(int n) {',
  '    F[0] = 0;',
  '    F[1] = 1;',
  '    for (int i = 2; i <= n; i++)',
  '        F[i] = F[i-2] + F[i-1];',
  '    return F[n];',
  '}'
]));
add(img(`Slide 6 (${DP})`, `Handwritten tabulation code and final array 0, 1, 1, 2, 3, 5, with a note that tabulation is bottom-up (0 to n) while memoization is top-down (from 5)`));
add(img(`Slide 16 (${DP2})`, `Boxed Fibonacci(n) pseudocode: F0 = 0, F1 = 1, for i = 2 to n do Fi = Fi-1 + Fi-2`));
add(tbl([2400, 1600, 5026], [
  ['Method', 'Time', 'Remark'],
  ['Plain recursion', 'O(2^{n})', 'Same calls repeated; T(n) = 2T(n-1) + 1 (upper bound)'],
  ['Memoization', 'O(n)', 'Each value computed once, repeats return the stored value'],
  ['Tabulation', 'O(n)', 'Loop from 0 to n; only the previous two values are needed']
]));
add(selfTest(
  `The notes use T(n) = 2T(n-1) + 1 to get O(2^n), but the real recursion is F(n-1) + F(n-2). Why is that replacement safe, and what does it say about the bound?`,
  `T(n-2) is smaller than T(n-1), so replacing it with T(n-1) can only overestimate the work. Hence O(2^n) is an upper bound, not an exact count.`
));

// =====================================================================
add(h1('0/1 KNAPSACK PROBLEM'));
add(h2('PROBLEM DEFINITION'));
add(
  bullet(`Given **n items**, each with a weight and a profit, and a bag of capacity **W** (it holds at most W weight).`),
  bullet(`Goal: put items in the bag so that the **sum of profits is maximum**.`),
  bullet(`**0/1 constraint** – an item is put in completely or not at all. A part of an item cannot be taken.`),
  bullet(`Formally: maximize Σ p_{i}x_{i} subject to Σ w_{i}x_{i} ≤ W, where x_{i} = 1 if item i is taken and 0 otherwise.`),
  bullet(`**Eg:** W = 4, profit = [1, 2, 3], weight = [4, 5, 1] gives output 3.`),
  bullet(`Only two items have weight ≤ 4: weight 4 (profit 1) and weight 1 (profit 3).`, 1),
  bullet(`Both together weigh 5 > 4, so they cannot be taken together. Best profit is 3.`, 1),
  bullet(`**Eg:** W = 3, profit = [1, 2, 3], weight = [4, 5, 6] gives output 0 because no item fits.`)
);
add(img(`Slide 8 (${DP})`, `Two input/output examples for 0/1 Knapsack (W = 4 with answer 3, and W = 3 with answer 0) with the explanation`));

add(h2('NAIVE APPROACH: RECURSION'));
add(
  bullet(`Brute force: consider all subsets of items, compute total weight and value of each, keep only subsets whose weight is within W and pick the one with maximum value.`),
  bullet(`**Optimal substructure** – for every item there are two cases:`),
  bullet(`**Case 1:** the item is included in the optimal subset.`, 1),
  bullet(`**Case 2:** the item is not included.`, 1),
  bullet(`Best value from n items is the maximum of:`),
  bullet(`**Pick the nth item** – value of nth item + best value from the remaining n-1 items with capacity W - weight of nth item.`, 1),
  bullet(`**Do not pick the nth item** – best value from n-1 items with capacity W.`, 1),
  bullet(`If the weight of the nth item is greater than W, it cannot be included, so the second case is the only possibility.`),
  bullet(`Time **O(2^{n})**, space **O(n)** (recursion depth).`)
);

add(h2('TOP-DOWN DP (MEMOIZATION)'));
add(
  bullet(`The recursion solves the same subproblem again and again (overlapping subproblems).`),
  bullet(`A subproblem is described by its state (n, w): number of remaining items and remaining capacity.`),
  bullet(`Use a **2-D array** to store each state. The first time a state appears, compute and store it. If the same state appears again, return the stored value in constant time.`),
  bullet(`Time and space: **O(n × W)**.`)
);
add(img(`Slide 11 (${DP})`, `Recursion tree K(remaining items, capacity) for weight = {1, 1, 1}, W = 2, value = {10, 20, 30} with choose/not choose branches and repeated states such as K(1,1), K(0,0) and K(0,1)`));

add(h2('BOTTOM-UP DP (TABULATION)'));
add(
  bullet(`Two parameters change in the recursion: items (0 to n) and capacity (0 to W). So build a 2-D table of size **(n+1) × (W+1)**.`),
  bullet(`**V[i][j]** (also written dp[i][j]) – maximum value obtainable using the first i items with knapsack capacity j.`),
  bullet(`**Base case** – row 0 (no items) and column 0 (no capacity) are all 0. In class the zero row and column were created and filled first.`),
  bullet(`For each item i and capacity j, decide whether to pick the item:`),
  bullet(`**Leave item i** – value stays the same as with the previous items: V[i-1][j].`, 1),
  bullet(`**Take item i** – gain v_{i} but use up w_{i} of the capacity. Fill the remaining j - w_{i} in the best way with the first i-1 items: v_{i} + V[i-1][j - w_{i}]. Only possible if w_{i} ≤ j.`, 1),
  bullet(`The answer is **V[n][W]**.`)
);
add(code([
  'V[0][j] = 0                                         for 0 <= j <= W',
  'V[i][j] = V[i-1][j]                                 if w[i] > j',
  'V[i][j] = max(V[i-1][j], v[i] + V[i-1][j - w[i]])   if w[i] <= j'
]));
add(detail([
  `Why this works: solutions to larger subproblems can be built easily from solutions to smaller ones. V[i][j] stores the maximum value of any set of objects {1, 2, ..., i} that fits in a knapsack of weight j.`,
  `The table is filled top-down (row by row) and left to right.`
]));
add(img(`Slide 12 (${DP})`, `Text slide on the bottom-up approach (dp[i][j] formula with pick and not-pick cases)`));
add(img(`Slides 2-3 (${KN})`, `Matrix V[0..n, 0..W] explanation and the recursive formulation of V[i, j] with the Leave object i / Take object i cases`));
add(tbl([4026, 2500, 2500], [
  ['Approach', 'Time', 'Space'],
  ['Naive recursion', 'O(2^{n})', 'O(n)'],
  ['Top-down DP (memoization)', 'O(n × W)', 'O(n × W)'],
  ['Bottom-up DP (tabulation)', 'O(n × W)', 'O(n × W)']
]));

add(h2('ALGORITHM AND COMPLEXITY'));
add(code([
  'KnapSack(v, w, n, W)',
  '    for j = 0 to W',
  '        V[0][j] = 0',
  '    for i = 1 to n',
  '        for j = 0 to W',
  '            if (w[i] <= j)',
  '                V[i][j] = max(V[i-1][j], v[i] + V[i-1][j - w[i]])',
  '            else',
  '                V[i][j] = V[i-1][j]',
  '    return V[n][W]'
]));
add(
  bullet(`Two nested loops over n items and W capacities give time **O(n·W)**. The table needs space O(n·W).`),
  bullet(`As n and W get large, both time and space become significant.`)
);
add(img(`Slide 9 (${KN})`, `KnapSack(v, w, n, W) pseudocode with the time complexity O(nW) note`));

add(h2('TRACING BACK THE CHOSEN ITEMS'));
add(
  bullet(`Start at V[n][W] with j = W. Go through items i = n down to 1:`),
  bullet(`If V[i][j] ≠ V[i-1][j], item i is **taken** (x_{i} = 1) and j becomes j - w_{i}.`, 1),
  bullet(`If V[i][j] = V[i-1][j], item i is **not taken** (x_{i} = 0).`, 1),
  bullet(`The handwritten solutions do the same thing by subtracting profits from the answer until 0 is reached (e.g. 8 - 6 = 2, 2 - 2 = 0).`)
);

add(h2('WORKED EXAMPLE 1: W = 11, FIVE ITEMS'));
add(tbl([3000, 3013, 3013], [
  ['Item', 'Weight (w)', 'Value (v)'],
  ['1', '1', '1'],
  ['2', '2', '6'],
  ['3', '5', '18'],
  ['4', '6', '22'],
  ['5', '7', '28']
], { numeric: true }));
add(
  bullet(`Row 1 is filled first: with only item 1 (w = 1, v = 1), V[1][j] = 1 for every j ≥ 1.`),
  bullet(`Then each cell uses V[i][j] = max(V[i-1][j], v_{i} + V[i-1][j - w_{i}]).`),
  bullet(`**Eg:** V[3][7] = max{V[2][7], 18 + V[2][7-5]} = max{7, 18 + 6} = 24.`)
);
add(dpTable(1886, 595, ['i (w, v)', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11'], [
  ['0 (none)', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'],
  ['1 (1, 1)', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'],
  ['2 (2, 6)', '0', '1', '6', '7', '7', '7', '7', '7', '7', '7', '7', '7'],
  ['3 (5, 18)', '0', '1', '6', '7', '7', '18', '19', '24', '25', '25', '25', '25'],
  ['4 (6, 22)', '0', '1', '6', '7', '7', '18', '22', '24', '28', '29', '29', '40'],
  ['5 (7, 28)', '0', '1', '6', '7', '7', '18', '22', '28', '29', '34', '35', { t: '40', hl: true }]
]));
add(
  bullet(`**Answer:** V[5][11] = 40.`),
  bullet(`**Trace back:** V[5][11] = V[4][11], so item 5 is not taken. V[4][11] ≠ V[3][11], so item 4 is taken (j = 11 - 6 = 5). V[3][5] ≠ V[2][5], so item 3 is taken (j = 0).`),
  bullet(`Items 3 and 4 are chosen: weight 5 + 6 = 11, value 18 + 22 = 40.`)
);
add(img(`Slides 4-5 (${KN})`, `Example statement with W = 11 and the empty table, then the table with row 1 filled (all 1s from weight 1 onwards)`));
add(img(`Slides 6-8 (${KN})`, `Step-by-step filling of the table (rows 1 to 3, then rows 1 to 4, then the full table) and the V[3,7] = 24 calculation`));

add(h2('WORKED EXAMPLE 2: M = 8, n = 4'));
add(
  bullet(`Weights w = {2, 3, 4, 5}, profits p = {1, 2, 5, 6}, capacity M = 8.`)
);
add(dpTable(2006, 780, ['i (w, p)', '0', '1', '2', '3', '4', '5', '6', '7', '8'], [
  ['0 (none)', '0', '0', '0', '0', '0', '0', '0', '0', '0'],
  ['1 (2, 1)', '0', '0', '1', '1', '1', '1', '1', '1', '1'],
  ['2 (3, 2)', '0', '0', '1', '2', '2', '3', '3', '3', '3'],
  ['3 (4, 5)', '0', '0', '1', '2', '5', '5', '6', '7', '7'],
  ['4 (5, 6)', '0', '0', '1', '2', '5', '6', '6', '7', { t: '8', hl: true }]
]));
add(
  bullet(`**Answer:** V[4][8] = 8 with x = (0, 1, 0, 1), that is items 2 and 4: weight 3 + 5 = 8, profit 2 + 6 = 8.`),
  bullet(`The slide first states the general formula V[i, w] = max{V[i-1, w], V[i-1, w - w_{i}] + P[i]}.`)
);
add(img(`Slide 14 (${DP})`, `Handwritten tabulation table for M = 8, n = 4 (w = {2,3,4,5}, p = {1,2,5,6}) with the knapsack formula box and the x1..x4 = 0 1 0 1 selection`));

add(h2('WORKED EXAMPLE 3: M = 5, n = 4'));
add(
  bullet(`Weights w = {1, 2, 4, 5}, profits p = {5, 4, 8, 6}, capacity M = 5.`)
);
add(dpTable(2726, 1050, ['i (w, p)', '0', '1', '2', '3', '4', '5'], [
  ['0 (none)', '0', '0', '0', '0', '0', '0'],
  ['1 (1, 5)', '0', '5', '5', '5', '5', '5'],
  ['2 (2, 4)', '0', '5', '5', '9', '9', '9'],
  ['3 (4, 8)', '0', '5', '5', '9', '9', '13'],
  ['4 (5, 6)', '0', '5', '5', '9', '9', { t: '13', hl: true }]
]));
add(
  bullet(`**Answer:** V[4][5] = 13 with x = (1, 0, 1, 0), that is items 1 and 3: weight 1 + 4 = 5, profit 5 + 8 = 13.`)
);
add(img(`Slides 13 and 15 (${DP})`, `Handwritten problem statement and constraint (Max Σ Pi Xi, Σ wi ≤ M) on slide 13, and the handwritten table for M = 5 with the selection x1..x4 = 1 0 1 0 on slide 15`));
add(selfTest(
  `In the take case we use V[i-1][j - w_i]. What would change if we wrote V[i][j - w_i] instead?`,
  `Item i could be counted again inside its own subproblem, so the same item could be taken many times. That breaks the 0/1 rule.`
));
add(selfTest(
  `When w_i > j, why can we not simply apply the max formula anyway?`,
  `j - w_i would be negative, which is not a valid column, and the item physically does not fit. So we must copy V[i-1][j].`
));

// =====================================================================
add(h1('MATRIX CHAIN MULTIPLICATION'));
add(h2('BASICS OF MATRIX MULTIPLICATION'));
add(
  bullet(`**Condition** – two matrices can be multiplied only if the number of columns of M_{1} equals the number of rows of M_{2}.`),
  bullet(`If M_{1} is m × n and M_{2} is n × p, the result is m × p and needs **m × n × p** scalar multiplications.`),
  bullet(`**Eg:** M_{1} (2 × 3) times M_{2} (3 × 2) gives a 2 × 2 matrix and takes 2 × 3 × 2 = 12 multiplications. Each entry is a sum of 3 products, e.g. c_{11} = a_{11}b_{11} + a_{12}b_{21} + a_{13}b_{31}.`)
);
add(img(`Slide 18 (${DP})`, `Handwritten matrix multiplication example: M1 is 2×3, M2 is 3×2, the resulting 2×2 matrix C entries and total 2×3×2 = 12`));

add(h2('THE MATRIX CHAIN PROBLEM'));
add(
  bullet(`Given the dimensions of a chain of matrices in an array arr[] (d_{0}, d_{1}, ..., d_{n}), where the i-th matrix has dimension arr[i-1] × arr[i].`),
  bullet(`Task: find the most efficient way to multiply them, that is the one with the **minimum total number of element multiplications**.`),
  bullet(`Multiplication is associative, so we are only choosing **where to put the brackets**. The order changes the cost, not the result.`),
  bullet(`**Eg:** A_{1} (2×3), A_{2} (3×4), A_{3} (4×2):`),
  bullet(`(A_{1}A_{2})A_{3}: 2·3·4 = 24 gives a 2×4 matrix, then 2·4·2 = 16. Total **40**.`, 1),
  bullet(`A_{1}(A_{2}A_{3}): 3·4·2 = 24 gives a 3×2 matrix, then 2·3·2 = 12. Total **36**.`, 1),
  bullet(`The second order is better because it needs fewer multiplications.`, 1)
);
add(img(`Slide 19 (${DP})`, `Handwritten A1 × A2 × A3 example comparing (A1A2)A3 = 24 + 16 = 40 with A1(A2A3) = 24 + 12 = 36`));
add(tbl([1900, 2800, 1800, 2526], [
  ['arr[]', 'Matrices', 'Minimum multiplications', 'Best order'],
  ['[2, 1, 3, 4]', '2×1, 1×3, 3×4', '20', 'M1(M2M3): 1·3·4 + 2·1·4 = 20 (the other order gives 30)'],
  ['[1, 2, 3, 4, 3]', '1×2, 2×3, 3×4, 4×3', '30', '((M1M2)M3)M4: 1·2·3 + 1·3·4 + 1·4·3 = 30'],
  ['[3, 4]', 'one matrix, 3×4', '0', 'Only one matrix, so no multiplication is needed']
]));
add(img(`Slide 17 (${DP})`, `Three input/output examples for matrix chain multiplication (arr = [2,1,3,4] gives 20, arr = [1,2,3,4,3] gives 30, arr = [3,4] gives 0) with explanations`));
add(
  bullet(`**Brute force** – find every possible bracketing and select the best.`),
  bullet(`The number of ways to bracket n matrices is the Catalan number **C_{n-1}**, where C_{n} = (1 / (n+1)) × (2n choose n).`),
  bullet(`**Eg:** 4 matrices have C_{3} = 5 ways:`),
  bullet(`A_{1}(A_{2}(A_{3}A_{4}))`, 1),
  bullet(`A_{1}((A_{2}A_{3})A_{4})`, 1),
  bullet(`(A_{1}A_{2})(A_{3}A_{4})`, 1),
  bullet(`(A_{1}(A_{2}A_{3}))A_{4}`, 1),
  bullet(`((A_{1}A_{2})A_{3})A_{4}`, 1),
  bullet(`Checking every bracketing separately is wasteful, so DP is used.`)
);
add(img(`Slides 20-21 (${DP})`, `Handwritten slide asking about n matrices M1 x M2 x ... x Mn (dynamic approach: find all solutions and select the best), and the slide listing the possible multiplication methods for A1..A4 with the Catalan formula`));

add(h2('DP FORMULA'));
add(
  bullet(`**C[i, j]** – minimum cost of multiplying the matrices A_{i} to A_{j}.`),
  bullet(`**k** – the split point between A_{i}..A_{k} and A_{k+1}..A_{j}.`)
);
add(code([
  'C[i][i] = 0',
  'C[i][j] = min over i <= k < j of { C[i][k] + C[k+1][j] + d[i-1] * d[k] * d[j] }'
]));
add(
  bullet(`The three parts of the cost: cost of the left part C[i, k], cost of the right part C[k+1, j], and the cost of multiplying the two resulting matrices (d_{i-1} × d_{k} times d_{k} × d_{j}), which is d_{i-1}·d_{k}·d_{j}.`),
  bullet(`C[i, i] = 0 because a single matrix (self multiplication) needs no multiplication.`),
  bullet(`**Issue:** C[1, 4] needs C[2, 4], C[1, 2], C[3, 4] and others, which themselves need further values.`),
  bullet(`**Solution:** find the smaller values first. Order of filling:`),
  bullet(`C[1,1], C[2,2], C[3,3], C[4,4] = 0`, 1),
  bullet(`C[1,2], C[2,3], C[3,4]`, 1),
  bullet(`C[1,3], C[2,4]`, 1),
  bullet(`C[1,4]`, 1),
  bullet(`A second table **K[i, j]** stores the k that gave the minimum, so the bracketing can be rebuilt afterwards.`)
);
add(img(`Slide 22 (${DP})`, `Handwritten formula, example chain A1..A4 with dimensions d0..d4, expansion of C[1,4] for k = 1, 2, 3 and the note on finding smaller values first`));

add(h2('WORKED EXAMPLE'));
add(
  bullet(`A_{1}: 2×3, A_{2}: 3×4, A_{3}: 4×2, A_{4}: 2×3, so (d_{0}, d_{1}, d_{2}, d_{3}, d_{4}) = (2, 3, 4, 2, 3).`),
  bullet(`**Length 2:**`),
  bullet(`C[1,2] = 2·3·4 = 24`, 1),
  bullet(`C[2,3] = 3·4·2 = 24`, 1),
  bullet(`C[3,4] = 4·2·3 = 24`, 1),
  bullet(`**Length 3:**`),
  bullet(`C[1,3] = min{k=1: 0 + 24 + 2·3·2 = 36, k=2: 24 + 0 + 2·4·2 = 40} = **36** (k = 1)`, 1),
  bullet(`C[2,4] = min{k=2: 0 + 24 + 3·4·3 = 60, k=3: 24 + 0 + 3·2·3 = 42} = **42** (k = 3)`, 1),
  bullet(`**Length 4:**`),
  bullet(`C[1,4] = min{k=1: 0 + 42 + 2·3·3 = 60, k=2: 24 + 24 + 2·4·3 = 72, k=3: 36 + 0 + 2·2·3 = 48} = **48** (k = 3)`, 1)
);
add(tbl([1826, 1800, 1800, 1800, 1800], [
  ['C[i, j]', 'j = 1', 'j = 2', 'j = 3', 'j = 4'],
  ['i = 1', '0', '24', '36', { t: '48', hl: true }],
  ['i = 2', '', '0', '24', '42'],
  ['i = 3', '', '', '0', '24'],
  ['i = 4', '', '', '', '0']
], { numeric: true }));
add(tbl([1826, 1800, 1800, 1800, 1800], [
  ['K[i, j]', 'j = 1', 'j = 2', 'j = 3', 'j = 4'],
  ['i = 1', '', '1', '1', '3'],
  ['i = 2', '', '', '2', '3'],
  ['i = 3', '', '', '', '3']
], { numeric: true }));
add(
  bullet(`**Bracketing from K:** K[1,4] = 3 splits into (A_{1}A_{2}A_{3})(A_{4}); K[1,3] = 1 splits the first part into A_{1}(A_{2}A_{3}).`),
  bullet(`Optimal order: **((A_{1}(A_{2}A_{3}))A_{4})** with minimum cost **48**.`)
);
add(detail([
  `The table has about n² entries and each entry tries up to n-1 split points, so the time is O(n³) and the space is O(n²).`
]));
add(img(`Slide 23 (${DP})`, `Handwritten strategy (smaller values first) with the C table being filled (diagonal zeros, C[1,2] = 24 and the row/column values 24, 36, 48, 42, 24)`));
add(img(`Slide 24 (${DP})`, `Handwritten calculation of C[2,3], C[3,4] and C[1,3] with the K table (split points) on the right`));
add(img(`Slide 25 (${DP})`, `Handwritten calculation of C[2,4] = 42 and C[1,4] = 48 for k = 1, 2, 3 with final bracketing ((A1)(A2 A3)) A4`));
add(selfTest(
  `Does changing the bracketing change the final product matrix? Does it change the cost?`,
  `The final matrix is the same because matrix multiplication is associative. Only the number of scalar multiplications changes, which is why we minimise it.`
));

// =====================================================================
add(h1('LONGEST COMMON SUBSEQUENCE (LCS)'));
add(h2('PROBLEM DEFINITION'));
add(
  bullet(`Given two strings s1 and s2, find the **length** of their Longest Common Subsequence. If there is no common subsequence, the answer is 0.`),
  bullet(`**Subsequence** – a string generated from the original by deleting 0 or more characters without changing the relative order of the remaining characters.`),
  bullet(`**Eg:** subsequences of "ABC" are "", "A", "B", "C", "AB", "AC", "BC" and "ABC".`),
  bullet(`A string of length n has **2^{n}** subsequences, so checking all of them is expensive.`)
);
add(tbl([2000, 2000, 1400, 3626], [
  ['s1', 's2', 'Length', 'LCS'],
  ['ABC', 'ACD', '2', `"AC"`],
  ['AGGTAB', 'GXTXAYB', '4', `"GTAB"`],
  ['ABC', 'CBA', '1', `"A", "B" or "C" (three LCS of length 1, so the LCS need not be unique)`]
]));
add(img(`Slide 27 (${DP})`, `Three LCS input/output examples (ABC/ACD gives 2, AGGTAB/GXTXAYB gives 4, ABC/CBA gives 1) with explanations`));

add(h2('RECURSIVE IDEA AND MEMOIZATION'));
add(
  bullet(`Compare the last characters of the two strings:`),
  bullet(`**Equal** – they are part of the LCS: 1 + LCS of both strings without their last characters.`, 1),
  bullet(`**Different** – skip the last character of s1 or skip the last character of s2 and take the larger result.`, 1),
  bullet(`**Eg:** L("AXYT", "AYZX"): last characters T and X differ, so it branches into L("AXY", "AYZX") and L("AXYT", "AYZ"). Further down, L("AXY", "AYZ") appears twice, so subproblems **overlap**.`),
  bullet(`**Memoization (top-down):** use a 2-D table of size (m+1) × (n+1) initialised to -1. Check it before every recursive call to avoid recomputing overlapping subproblems.`),
  bullet(`Time **O(m × n)**, space **O(m × n)**.`)
);
add(img(`Slide 29 (${DP})`, `Memoization recursion tree for L("AXYT", "AYZX") with Skip last character of S1 / S2 branches and the repeated node L("AXY", "AYZ") highlighted in green`));

add(h2('BOTTOM-UP DP (TABULATION)'));
add(
  bullet(`Two parameters change in the recursion, going from 0 to m and 0 to n. Create a 2-D dp table of size **(m+1) × (n+1)**.`),
  bullet(`First fill the known entries: row 0 and column 0 are all 0 (an empty string has no common subsequence).`),
  bullet(`Then fill the remaining entries with the formula below.`),
  bullet(`Time **O(m × n)**, space **O(m × n)**. The answer is dp[m][n].`)
);
add(code([
  'if s1[i-1] == s2[j-1]:',
  '    dp[i][j] = 1 + dp[i-1][j-1]',
  'else:',
  '    dp[i][j] = max(dp[i-1][j], dp[i][j-1])'
]));
add(img(`Slide 30 (${DP})`, `Text slide describing bottom-up LCS (2-D dp array of size (m+1) x (n+1), fill known entries first, then use the formula)`));

add(h2('WORKED EXAMPLE'));
add(
  bullet(`S1 = "AXYT" (rows) and S2 = "AYZX" (columns).`),
  bullet(`Step 1: dp[1][1]: A = A, so dp[1][1] = 1 + dp[0][0] = 1. For dp[1][2], A ≠ Y so dp[1][2] = max(dp[0][2], dp[1][1]) = 1. The rest of row 1 follows the same way.`),
  bullet(`Step 2: dp[2][1]: X ≠ A, so dp[2][1] = max(dp[1][1], dp[2][0]) = 1. Row 2 continues in the same way (dp[2][4] = 2 because X = X).`),
  bullet(`Step 3: dp[3][1]: Y ≠ A, so dp[3][1] = max(dp[2][1], dp[3][0]) = 1.`),
  bullet(`Step 4: dp[4][1]: T ≠ A, so dp[4][1] = max(dp[4][0], dp[3][1]) = 1.`)
);
add(dpTable(1826, 1440, ['S1 \\ S2', '0 (empty)', 'A', 'Y', 'Z', 'X'], [
  ['0 (empty)', '0', '0', '0', '0', '0'],
  ['A', '0', '1', '1', '1', '1'],
  ['X', '0', '1', '1', '1', '2'],
  ['Y', '0', '1', '2', '2', '2'],
  ['T', '0', '1', '2', '2', { t: '2', hl: true }]
], 22));
add(
  bullet(`**Answer:** dp[4][4] = 2 (for example "AY" or "AX").`),
  bullet(`The slide text writes S1 as "AXTY" but its table and recursion tree use the order A, X, Y, T.`)
);
add(img(`Slide 31 (${DP})`, `Initial 5x5 dp matrix with first row and column 0, and Step 01: dp[1][1] = 1 + dp[0][0] with row 1 filled (1 1 1 1)`));
add(img(`Slide 32 (${DP})`, `Step 02 (dp[2][1] = max(dp[1][1], dp[2][0]), row 2 = 1 1 1 2) and Step 03 (dp[3][1], row 3 = 1 2 2 2) tables`));
add(img(`Slide 33 (${DP})`, `Step 04: dp[4][1] = max(dp[4][0], dp[3][1]) and the complete table with the final answer 2 circled`));
add(selfTest(
  `On a match we write dp[i][j] = 1 + dp[i-1][j-1]. Why would it be wrong to use max(dp[i-1][j], dp[i][j-1]) on a match as well?`,
  `It would never add the matched character. For s1 = "A" and s2 = "A" it gives max(0, 0) = 0 instead of 1.`
));

// =====================================================================
add(h1('PROBLEM SET'));
add(p(`**Q1 (Numerical, Knapsack).** Capacity W = 7 and items (weight, value): (1, 1), (3, 4), (4, 5), (5, 7). Fill the DP table and find the maximum value and the items chosen.`));
add(p(`**Answer:**`));
add(dpTable(2226, 850, ['i (w, v)', '0', '1', '2', '3', '4', '5', '6', '7'], [
  ['0 (none)', '0', '0', '0', '0', '0', '0', '0', '0'],
  ['1 (1, 1)', '0', '1', '1', '1', '1', '1', '1', '1'],
  ['2 (3, 4)', '0', '1', '1', '4', '5', '5', '5', '5'],
  ['3 (4, 5)', '0', '1', '1', '4', '5', '6', '6', '9'],
  ['4 (5, 7)', '0', '1', '1', '4', '5', '7', '8', { t: '9', hl: true }]
]));
add(bullet(`Maximum value = V[4][7] = 9. V[4][7] = V[3][7], so item 4 is not taken. V[3][7] ≠ V[2][7], so item 3 is taken (j = 3). V[2][3] ≠ V[1][3], so item 2 is taken (j = 0). Items 2 and 3: weight 7, value 9.`));

add(p(`**Q2 (Numerical, Matrix Chain).** Matrices have dimensions arr[] = [10, 20, 5, 30]. Find the minimum number of multiplications and the best bracketing.`));
add(p(`**Answer:**`));
add(
  bullet(`C[1,2] = 10·20·5 = 1000 and C[2,3] = 20·5·30 = 3000.`),
  bullet(`C[1,3] = min{k=1: 0 + 3000 + 10·20·30 = 9000, k=2: 1000 + 0 + 10·5·30 = 2500} = 2500 (k = 2).`),
  bullet(`Minimum = **2500** with the bracketing (A_{1}A_{2})A_{3}.`)
);

add(p(`**Q3 (Numerical, LCS).** Find the LCS length of s1 = "ABCD" and s2 = "ACBD" using the dp table.`));
add(p(`**Answer:**`));
add(dpTable(1826, 1440, ['S1 \\ S2', '0 (empty)', 'A', 'C', 'B', 'D'], [
  ['0 (empty)', '0', '0', '0', '0', '0'],
  ['A', '0', '1', '1', '1', '1'],
  ['B', '0', '1', '1', '2', '2'],
  ['C', '0', '1', '2', '2', '2'],
  ['D', '0', '1', '2', '2', { t: '3', hl: true }]
], 22));
add(bullet(`LCS length = 3 (for example "ABD" or "ACD").`));

add(p(`**Q4 (Counting).** In how many ways can a chain of 5 matrices be fully bracketed?`));
add(p(`**Answer:** C_{4} = (1/5) × (8 choose 4) = 70 / 5 = **14** ways (n matrices give C_{n-1}).`));

add(p(`**Q5 (Reasoning).** How many cells does the table have for a knapsack with n = 50 items and W = 1000, and for an LCS of strings of length 30 and 20 (including the zero row and column)?`));
add(p(`**Answer:** Knapsack: (50+1) × (1000+1) = 51 × 1001 = **51,051** cells. LCS: (30+1) × (20+1) = 31 × 21 = **651** cells.`));

add(p(`**Q6 (Reasoning, Fibonacci).** When fib(5) is evaluated with plain recursion, how many times is fib(2) called? With memoization, how many times is fib(2) actually computed?`));
add(p(`**Answer:** Plain recursion calls fib(2) **3 times** (once from each of the two fib(3) calls and once directly from fib(4)). With memoization it is computed **once**; later requests return the stored value.`));

add(p(`**Q7 (Reasoning, Matrix Chain).** What does the K table store and why is it needed when the C table already gives the minimum cost?`));
add(p(`**Answer:** K[i, j] stores the split point k that gave the minimum for C[i, j]. C only gives the cost, so K is needed to rebuild the actual optimal bracketing.`));

// ---------- document ----------
const doc = new Document({
  creator: 'Syed Sultan',
  title: 'Dynamic Programming Notes',
  styles: {
    default: {
      document: {
        run: { font: FONT, size: 24 },
        paragraph: { spacing: { line: 276, after: 80 } }
      }
    },
    paragraphStyles: [
      {
        id: 'Title', name: 'Title', basedOn: 'Normal', next: 'Normal', quickFormat: true,
        run: { font: FONT, size: 40, bold: true, allCaps: true, color: '000000' },
        paragraph: { alignment: AlignmentType.CENTER, spacing: { before: 120, after: 240 } }
      },
      {
        id: 'Heading1', name: 'Heading 1', basedOn: 'Normal', next: 'Normal', quickFormat: true,
        run: { font: FONT, size: 32, bold: true, allCaps: true, color: '000000' },
        paragraph: { alignment: AlignmentType.LEFT, spacing: { before: 360, after: 120 }, outlineLevel: 0, keepNext: true }
      },
      {
        id: 'Heading2', name: 'Heading 2', basedOn: 'Normal', next: 'Normal', quickFormat: true,
        run: { font: FONT, size: 28, bold: true, allCaps: true, color: '000000' },
        paragraph: { alignment: AlignmentType.LEFT, spacing: { before: 240, after: 80 }, outlineLevel: 1, keepNext: true }
      }
    ]
  },
  numbering: {
    config: [{
      reference: 'bullets',
      levels: [
        { level: 0, format: LevelFormat.BULLET, text: '•', alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 720, hanging: 360 } } } },
        { level: 1, format: LevelFormat.BULLET, text: '–', alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 1260, hanging: 360 } } } }
      ]
    }]
  },
  sections: [{
    properties: {
      page: {
        size: { width: 11906, height: 16838 },
        margin: { top: 1440, right: 1440, bottom: 1440, left: 1440 }
      }
    },
    headers: {
      default: new Header({
        children: [new Paragraph({
          border: { bottom: { style: BorderStyle.SINGLE, size: 6, color: '000000', space: 4 } },
          spacing: { after: 120 },
          children: [
            new TextRun({ text: 'SYED SULTAN NOTES', bold: true, font: FONT, size: 22 }),
            new TextRun({ text: ' | Week 9 | ', font: FONT, size: 22 }),
            new TextRun({ text: 'DESIGN AND ANALYSIS OF ALGORITHMS', bold: true, font: FONT, size: 22 })
          ]
        })]
      })
    },
    footers: {
      default: new Footer({
        children: [new Paragraph({
          alignment: AlignmentType.CENTER,
          children: [new TextRun({ children: [PageNumber.CURRENT], font: FONT, size: 22 })]
        })]
      })
    },
    children: body
  }]
});

Packer.toBuffer(doc).then(buf => {
    fs.mkdirSync('./outputs', { recursive: true });
    fs.writeFileSync('./outputs/DAA_Week9_Notes_SyedSultan.docx', buf);
  console.log('done');
});