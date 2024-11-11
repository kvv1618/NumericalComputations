function x = pagerank2(U, G, p, tol, max_iter)
    if nargin < 3, p = 0.85; end
    if nargin < 4, tol = 1e-6; end  % Tolerance for convergence
    if nargin < 5, max_iter = 100; end  % Maximum number of iterations

    % Eliminate any self-referential links
    G = G - diag(diag(G));

    % Get size and compute out-degrees
    [n, ~] = size(G);
    c = sum(G, 1);

    % Scale columns to sum to 1 (or 0 where there are no out-links)
    k = find(c ~= 0);
    D = sparse(k, k, 1 ./ c(k), n, n);

    % Define matrix A and the vector e
    A = p * G * D;
    e = ones(n, 1);

    % Add a small regularization term to I - A to avoid division by zero
    reg_param = 1e-9;  % Regularization parameter
    I = speye(n, n);
    x = (I - A + reg_param * I) \ e;
    x = x / sum(x); % Normalize x to make it a probability distribution

end
