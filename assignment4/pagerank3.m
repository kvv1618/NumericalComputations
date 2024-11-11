function x = pagerank3(U, G, p, tol, max_iter)

    if nargin < 3, p = 0.85; end
    if nargin < 4, tol = 1e-6; end     % Tolerance for convergence
    if nargin < 5, max_iter = 100; end % Maximum number of iterations

    % Eliminate any self-referential links
    G = G - diag(diag(G));

    % Get size and compute out-degrees
    [n, ~] = size(G);
    c = sum(G, 1);  % Out-degree
    k = find(c ~= 0);
    D = sparse(k, k, 1 ./ c(k), n, n);

    e = ones(n, 1);

    % Modify G with damping factor
    G = p * G * D;
    z = ((1 - p) * (c ~= 0) + (c == 0)) / n;

    % Initialize the page rank vector x
    x = ones(n, 1) / n;

    % Power method iteration
    for iter = 1:max_iter
        x_old = x;
        x = G * x + e * (z * x);
        
        % Check for convergence using the termination test
        if norm(x - x_old, 1) < tol
            break;
        end
    end

    % Normalize x to make it a probability distribution
    x = x / sum(x);

end
